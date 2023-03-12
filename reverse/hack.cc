#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
    delete[] buffer;
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
    auto ret = ReadProcessMemory(hProcess, addr, buffer, nBytes, &bytesOfRead);
    assert(ret);
    for (int i = 0; i < bytesOfRead; ++i)
    {
        vec.push_back(buffer[i]);
    }
    delete[] buffer;
    return vec;
}

std::vector<uint8_t> readMemoryUntil(HANDLE hProcess, LPVOID addr, uint8_t byte)
{
    std::vector<uint8_t> vec;
    uint8_t buffer;
    size_t bytesOfRead;
    for (int i = 0;; ++i)
    {
        auto ret = ReadProcessMemory(hProcess, (uint8_t *)addr + i, &buffer, 1, &bytesOfRead);
        if (!ret)
        {
            LOG("failed to read memory " << (LPVOID)((uint8_t *)addr + i));
            LOG("error code: " << GetLastError());
            return {};
        }
        if (buffer == byte)
        {
            break;
        }
        vec.push_back(buffer);
    }
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
        0x0F,
        0x57,
        0xC0,
        0x0F,
        0x28,
        0xF0,
        0x48,
        0x8B,
        0x58,
        0x08,
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

void dump_string()
{
    auto pid = 8040;
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc)
    {
        LOG("failed to find module base!");
        return;
    }
    LPVOID addr = (LPVOID)0x0000017488D4BB60;
    auto bytesRead = readMemoryUntil(hProc, addr, 0);
    LOG("read " << bytesRead.size() << " bytes");
    CloseHandle(hProc);
    {
        std::string content;
        std::ofstream f("dump.js", std::ios::binary);
        if (!f.is_open())
        {
            LOG("failed to open file");
            return;
        }
        for_each(bytesRead.begin(), bytesRead.end(), [&](const uint8_t ch)
                 { content += (char)ch; });
        f << content;
    }
}

int inject(const string exePath, const string dllPath)
{

    HANDLE hProc, hThread;
    std::string filename;
    bool ret = createProcess(&hProc, &hThread, exePath.c_str());
    if (!ret)
    {
        LOG("failed to create process!");
        return 1;
    }
    ret = injectDll(hProc, dllPath);
    if (ret)
    {
        std::cout << "succeed to inject dll!\n";
    }
    else
    {
        std::cout << "failed to inject dll\n";
        goto cleanup;
    }
    ResumeThread(hThread);
cleanup:
    CloseHandle(hProc);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,
                    PSTR lpCmdLine, int nCmdShow)
{
    inject("D:\\Typora\\Typora.exe",
           "E:\\programming\\reverse\\typora\\hackTypora.dll");
    return 0;
}