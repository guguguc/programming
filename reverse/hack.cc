#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string processName = "a.exe";
const uint8_t jmp = 0xE9;
const uint8_t nop = 0x90;
const unsigned long long offset = 0xBBF9;
const unsigned long long noCdOffset = 0x46DE893;


template <typename T>
void extend_vec(vector<T> &destVec, const vector<T> &vec)
{
    for (const auto &val : vec)
    {
        destVec.push_back(val);
    }
}

void print(const std::vector<uint8_t> &vec)
{   
    for (const auto &byte : vec)
    {
        printf("%02hhx ", byte);
    }
    printf("\n");
}

bool write2file(std::string filename, const std::vector<uint8_t> &bytes)
{
    std::ofstream file(filename, ios::out | ios::binary);
    if (!file.is_open())
    {
        return false;
    }
    char *buffer = new char[bytes.size()]{0};
    int i = 0;
    for (const auto &byte : bytes)
    {
        buffer[i++] = byte;
    }
    file.write(buffer, bytes.size());
    delete []buffer;
    file.close();
    return true;
}


std::vector<uint8_t> calcJmpRaletiveAddr(LPVOID newAbsAddr, LPVOID patchAbsAddr)
{
    std::vector<uint8_t> ret;
    auto relativeAddr = int32_t((unsigned long long)newAbsAddr - (unsigned long long)patchAbsAddr - 5);
    for (int i = 0; i < 4; ++i)
    {
        ret.push_back((relativeAddr >> ((3 - i) * 8)) & 0xff);
    }
    return ret;
}


std::vector<uint8_t> readMemory(HANDLE hProcess, LPVOID addr, size_t nBytes)
{
    std::vector<uint8_t> vec;
    uint8_t *buffer = new uint8_t[0x20000000]{0};
    size_t bytesOfRead;
    ReadProcessMemory(hProcess, addr, buffer, nBytes, &bytesOfRead);
    for (int i = 0; i < bytesOfRead; ++i)
    {
        vec.push_back(buffer[i]);
    }
    delete []buffer;
    return vec;
}

bool writeMemory(HANDLE hProcess, LPVOID addr, const vector<uint8_t> &bytes)
{
    bool ret, err;
    char buffer[100];
    int i = 0;
    for (const auto &byte : bytes)
    {
        buffer[i++] = byte;
    }
    size_t bytesOfWrite;
    err = WriteProcessMemory(hProcess, addr, buffer, bytes.size(), &bytesOfWrite);
    return err && (bytesOfWrite == bytes.size());
}

bool freeMemory(HANDLE hProcess, LPVOID addr)
{
    auto ret = VirtualFreeEx(hProcess, addr, 0, MEM_DECOMMIT);
    return ret ? true : false;
}

LPVOID allocMemNearBy(HANDLE hProcess, LPVOID addr, DWORD flag)
{
    unsigned long long limit = (unsigned long long)1024 * 1024 * 1024 * 2;
    LPVOID newMemAddr = NULL;
    for (int i = 1; i * 2048 < limit; ++i)
    {
        newMemAddr = VirtualAllocEx(hProcess, (LPVOID)((unsigned long long)addr - i * 2048),
                                    2048, MEM_COMMIT | MEM_RESERVE, flag);
        if (newMemAddr)
        {
            break;
        }
    }
    return newMemAddr;
}

bool injectCode(HANDLE hProcess, LPVOID patchAddr)
{
    std::vector<uint8_t> code;
    code.push_back(jmp);
    LPVOID newMemAbsAddr = allocMemNearBy(hProcess, patchAddr, PAGE_EXECUTE_READWRITE);
    if (!newMemAbsAddr)
    {
        LOG("failed to allocate memory!");
        return false;
    }
    LOG(string("new mem addr: ") << newMemAbsAddr);
    std::vector<uint8_t> oprand = calcJmpRaletiveAddr(newMemAbsAddr, patchAddr);
    reverse(oprand.begin(), oprand.end());
    extend_vec(code, oprand);
    std::vector<uint8_t> padding{nop, nop};
    extend_vec(code, padding);
    LOG("stub jmp code:");
    print(code);
    if (!writeMemory(hProcess, patchAddr, code))
    {
        LOG("failed to write stub code!");
        return false;
    }
    std::vector<uint8_t> shellCode{
        0x0F, 0x57, 0xC0,
        0x0F, 0x28, 0xF0,
        0x48, 0x8B, 0x58, 0x08,
        jmp,
    };
    oprand = calcJmpRaletiveAddr(LPVOID((unsigned long long)(patchAddr) + 7),
                        LPVOID((unsigned long long)newMemAbsAddr + 10));
    reverse(oprand.begin(), oprand.end());
    extend_vec(shellCode, oprand);
    LOG("shellcode:")
    print(shellCode);
    if (!writeMemory(hProcess, newMemAbsAddr, shellCode))
    {
        LOG("failed to write shell code!");
    }
    return true;
}

int main()
{
    // bool ret = false;
    // auto pid = getProcessPid("YuanShen.exe");
    // if (!pid)
    // {
    //     LOG("failed to get pid!");
    //     return 1;
    // }
    // LOG("pid: " << pid);
    // HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    /*
    std::string dllPath("C:\\Users\\whato\\source\\repos\\hack\\x64\\Debug\\hack.dll");
    if (!getModuleBase(pid, "hack.dll"))
    {
        ret = injectDll(hProc, dllPath);
        if (!ret)
        {
            LOG("failed to inject dll!");
            CloseHandle(hProc);
            return 1;
        }
    }
    auto procBase = getModuleBase(pid, "UserAssembly.dll");
    if (!procBase)
    {
        LOG("failed to find module base!");
        CloseHandle(hProc);
        return 1;
    }
    LPVOID patchNoCdAddr = (LPVOID)((unsigned long long)procBase + noCdOffset);
    LOG("find patch NoCd addr:" << patchNoCdAddr);
    injectCode(hProc, patchNoCdAddr);
    */

    /*
    auto targetModule = getProcessModule(pid, "UnityPlayer.dll");
    if (!targetModule.moduleBase)
    {
        LOG("failed to get module!");
        return 1;
    }
    auto bytes = readMemory(hProc, targetModule.moduleBase, targetModule.moduleSize);
    write2file("UserAssembly-cheat.bin", bytes);
    */
    HANDLE hProc, hThread;
    bool ret = createProcess(&hProc, &hThread, "D:\\MHY\\Genshin Impact Game\\YuanShen.exe");
    if (!ret)
    {
        LOG("failed to create process!");
        return 1;
    }
    injectDll(hProc, "C:\\Users\\whato\\source\\repos\\hack\\x64\\Debug\\hack.dll");
    std::cout << "succeed to inject dll!\n";
    system("pause");
    ResumeThread(hThread);
    CloseHandle(hProc);
    return 0;
}