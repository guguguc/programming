#include <iostream>
#include <cstring>
#include <fmt/core.h>

using namespace std;

void dump_str(const char *s, size_t size)
{
    for (int i = 0; i < size; ++i)
        fmt::print("0x{:x} ", *(s+i));
}

int main()
{
    const char     *s1 = u8"abcdef";
    const char16_t *s2 = u"abcdef";
    const char32_t *s3 = U"abcdef";

    dump_str((const char*)s2, 6 * sizeof(char16_t));

    return 0;
}
