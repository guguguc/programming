#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#define DO_API(r, n, p) r (*n) p
DO_API(void, il2cpp_get_api_table, (void *));

int main()
{
    std::string dllPath("D:\\re\\3.4\\UserAssembly.dll");
    HMODULE hModule = LoadLibraryA(dllPath.c_str());
    std::cout << hModule << "\n";
    il2cpp_get_api_table = (void(*)(void*))GetProcAddress(hModule, "il2cpp_get_api_table");
    uint64_t table[1203];
    memset(table, 0, sizeof(uint64_t) * 1203);
    il2cpp_get_api_table(table);
    std::ifstream f("key.txt");
    std::ofstream fo("out.txt");
    for (int i = 0; i < 1202; ++i)
    {
        uint64_t key;
        f >> std::hex >> key;
        void *ptr = (void*)(key ^ table[i]);
        fo << "case: " << i << " key: " << key << "  " << "addr: " << ptr << "\n";
        if (i == 988)
        {
            fo << "found il2cpp_init\n";
        }
        else if (i == 337)
        {
            fo << "found il2cpp_class_from_name\n";
        }
        else if (i == 1189)
        {
            fo << "found il2cpp_class_get_methods\n";
        }
        else if (i == 1050)
        {
            fo << "found il2cpp_method_get_name\n";
        }
    }
    fo << "base: " << hModule << "\n";
    fo.close();
    system("pause");
    FreeLibrary(hModule);
    return 0;
}