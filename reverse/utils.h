#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <Psapi.h>
#include <memoryapi.h>

#define LOG(msg) std::cout << msg << std::endl;

struct ModuleInfo
{
    ModuleInfo() : moduleName(""), moduleBase(nullptr), moduleSize(0) {}
    ModuleInfo(std::string name, LPVOID base, size_t sz)
        : moduleName(name), moduleBase(base), moduleSize(sz) {}
    std::string moduleName;
    LPVOID moduleBase;
    size_t moduleSize;
};

bool injectDll(HANDLE handle, std::string dllPath);
DWORD getProcessPid(LPCTSTR lpProcessName);
ModuleInfo getProcessModule(DWORD pid, std::string moduleName);
bool createProcess(HANDLE* phProcess, HANDLE* phThread, const std::string path);

#endif