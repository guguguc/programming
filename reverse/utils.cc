#include "utils.h"

#include <wchar.h>
#include <stdlib.h>
#include <processthreadsapi.h>

#pragma comment(lib,"Advapi32.lib")

#undef UNICODE

bool injectDll(HANDLE handle, std::string dllPath)
{
    HMODULE hKernel = GetModuleHandle("kernel32.dll");
	if (hKernel == NULL)
	{
		LOG("[DLL Injection] Failed to get kernel32.dll module address.\n");
		return false;
	}

	LPVOID pLoadLibrary = (LPVOID)GetProcAddress(hKernel, "LoadLibraryA");
	if (pLoadLibrary == NULL) {
		LOG("[DLL Injection] Failed to get LoadLibraryA address.\n");
		return false;
	}

	LPVOID pDLLPath = VirtualAllocEx(handle, NULL, strlen(dllPath.c_str()) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (pDLLPath == NULL) {
		LOG("[DLL Injection] Failed to allocate memory for DLLPath in target process.\n");
		LOG(GetLastError());
		return false;
	}

	// Write the string name of our DLL in the memory allocated
	BOOL writeResult = WriteProcessMemory(handle, pDLLPath, dllPath.c_str(), strlen(dllPath.c_str()), NULL);
	if (writeResult == FALSE) {
		LOG("[DLL Injection] Failed to write remote process memory.\n");
		return false;
	}

	// Load our DLL by calling loadlibrary in the other process and passing our dll name
	HANDLE hThread = CreateRemoteThread(handle, NULL, NULL, (LPTHREAD_START_ROUTINE)pLoadLibrary, (LPVOID)pDLLPath, NULL, NULL);
	if (hThread == NULL) {
		LOG("[DLL Injection] Failed to create remote thread.\n");
		VirtualFreeEx(handle, pDLLPath, 0, MEM_RELEASE);
		return false;
	}

	// Waiting for thread end and release unnecessary data.
	if (WaitForSingleObject(hThread, 2000) == WAIT_OBJECT_0) 
	{
		// ILog("[DLL Injection] Remote thread ended successfully.\n");
		VirtualFreeEx(handle, pDLLPath, 0, MEM_RELEASE);
	}

	CloseHandle(hThread);

	// ILog("[DLL Injection] Successfully LoadLibraryA injection.\n");
	return true;
}

DWORD getProcessPid(LPCTSTR lpProcessName)
{
	DWORD Ret = 0;
	PROCESSENTRY32 p32;
	HANDLE lpSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (lpSnapshot == INVALID_HANDLE_VALUE)
	{
		return Ret;
	}
	p32.dwSize = sizeof(PROCESSENTRY32);
	::Process32First(lpSnapshot, &p32);
	do {
		if (!lstrcmp(p32.szExeFile, lpProcessName))
		{
			Ret = p32.th32ProcessID;
			break;
		}
	} while (::Process32Next(lpSnapshot, &p32));
	::CloseHandle(lpSnapshot);
	return Ret;
}

std::vector<ModuleInfo> getProcessModules(DWORD pid)
{
    std::vector<ModuleInfo> modules;
    HANDLE lpSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (lpSnapShot == INVALID_HANDLE_VALUE)
    {
        return {};
    }
    MODULEENTRY32 m32;
    m32.dwSize = sizeof(m32);
    Module32First(lpSnapShot, &m32);
    do {
        modules.push_back(ModuleInfo(std::string(m32.szModule), (LPVOID)m32.modBaseAddr, m32.modBaseSize));
    } while (Module32Next(lpSnapShot, &m32));
    CloseHandle(lpSnapShot);
    return modules;
}

ModuleInfo getProcessModule(DWORD pid, std::string moduleName)
{
    auto modules = getProcessModules(pid);
    for (const auto &module : modules)
    {
        if (module.moduleName == moduleName)
        {
            return module;
        }
    }
    return ModuleInfo();
}

bool createProcess(HANDLE* phProcess, HANDLE* phThread, const std::string path)
{
	HANDLE hToken;
	BOOL TokenRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
	if (!TokenRet) 
	{
		LOG("Privilege escalation failed!");
		return false;
	}

	DWORD pid = getProcessPid("explorer.exe");
	if (pid == 0)
	{
		LOG("Can't find 'explorer' pid!");
		return false;
	}

	std::string CurrentDirectory = path;
	int pos = CurrentDirectory.rfind("\\", CurrentDirectory.length());
	CurrentDirectory = CurrentDirectory.substr(0, pos);

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		
	SIZE_T lpsize = 0;
	InitializeProcThreadAttributeList(NULL, 1, 0, &lpsize);
	
	char* temp = new char[lpsize];
	LPPROC_THREAD_ATTRIBUTE_LIST AttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)temp;
	InitializeProcThreadAttributeList(AttributeList, 1, 0, &lpsize);
	if (!UpdateProcThreadAttribute(AttributeList, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, 
		&handle, sizeof(HANDLE), NULL, NULL))
	{
		LOG("UpdateProcThreadAttribute failed !" << GetLastError());
	}
	
	STARTUPINFOEXA si{};
	si.StartupInfo.cb = sizeof(si);
	si.lpAttributeList = AttributeList;
	
	PROCESS_INFORMATION pi{};
	BOOL result = CreateProcessAsUserA(hToken, const_cast<LPSTR>(path.c_str()), nullptr,
		0, 0, 0, EXTENDED_STARTUPINFO_PRESENT | CREATE_SUSPENDED, 0,
		(LPSTR)CurrentDirectory.data(), (LPSTARTUPINFOA)&si, &pi);

	bool isOpened = result;
	if (isOpened)
	{
		*phThread = pi.hThread;
		*phProcess = pi.hProcess;
	}

	DeleteProcThreadAttributeList(AttributeList);
	delete[] temp;
	return isOpened;
}
