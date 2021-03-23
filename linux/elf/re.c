#include "helper.h"
#include <fcntl.h>
#include <stdio.h>

void elf_register(pelf_t proc)
{
    proc->elf_init = elf_init;
}

int main(int argc, char *argv[])
{
    const char *filename = argc > 1 ? argv[1] : "a.out";
    elf_t proc;
    elf_register(&proc);

    return 0;
}
