#ifndef __HELPER__
#define __HELPER__

#include <elf.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define SECTION_ITEM(X) [X] = #X

#define SECTION_TYPE_MAP(TYPE) (((TYPE) >= 20) ? ("SHT_UNKOWN") \
    : (SECTION_TYPE_TABLE[(TYPE)]))

static const char *SECTION_TYPE_TABLE[20] = {
    SECTION_ITEM(SHT_NULL),
    SECTION_ITEM(SHT_PROGBITS),
    SECTION_ITEM(SHT_SYMTAB),
    SECTION_ITEM(SHT_STRTAB),
    SECTION_ITEM(SHT_RELA),
    SECTION_ITEM(SHT_HASH),
    SECTION_ITEM(SHT_DYNAMIC),
    SECTION_ITEM(SHT_NOTE),
    SECTION_ITEM(SHT_NOBITS),
    SECTION_ITEM(SHT_REL),
    SECTION_ITEM(SHT_SHLIB),
    SECTION_ITEM(SHT_DYNSYM),
    SECTION_ITEM(SHT_INIT_ARRAY),
    SECTION_ITEM(SHT_FINI_ARRAY),
    SECTION_ITEM(SHT_PREINIT_ARRAY),
    SECTION_ITEM(SHT_GROUP),
    SECTION_ITEM(SHT_SYMTAB_SHNDX),
    SECTION_ITEM(SHT_NUM)
};

typedef struct elf elf_t;
typedef struct elf *pelf_t;

struct elf {
    int fd;
    Elf64_Ehdr *elfhdr;
    Elf64_Shdr *sechdrs;
    Elf64_Phdr *prohdrs;
    // operations
    void (*elf_init)(pelf_t self, const char *filename);
    void (*elf_read_elfhdr)(pelf_t self);
    void (*elf_read_sechdrs)(pelf_t self);
    void (*elf_read_prohdrs)(pelf_t self);
    void (*elf_parse)(pelf_t self);
    void (*elf_free)(pelf_t self);
};

#endif
