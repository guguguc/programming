#include "list.h"
#include "helper.h"
#include <sys/stat.h>
#include <sys/procfs.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DEFAULT_ELF_HEADER_SIZE 256
#define elfhdr_fieds_num 14
#define TRUE 1
#define FALSE 0

static char *get_prog_seg_type(uint32_t type)
{
    switch(type) {
        case PT_NULL: return "NULL";
        case PT_LOAD: return "LOAD";
        case PT_DYNAMIC: return "DYNAMIC";
        case PT_INTERP: return "INTERP";
        case PT_NOTE: return "NOTE";
        case PT_SHLIB: return "RESERVED";
        case PT_PHDR: return "ITSELF";
        case PT_LOPROC: return "LOPROC";
        case PT_HIPROC: return "HIPROC";
        case PT_GNU_PROPERTY: return "GNU_PROPERTY";
        case PT_GNU_EH_FRAME: return "GNU_EH_FRAME";
        case PT_GNU_STACK: return "GNU_STACK";
        case PT_GNU_RELRO: return "GNU_RELRO";
        default: return "UNKOWN";
    }
}

static char *get_prog_seg_flags(uint32_t flags)
{
    switch(flags) {
        case PF_X: return "X";
        case PF_R: return "R";
        case PF_W: return "W";
        case PF_X | PF_R: return "XR";
        case PF_X | PF_W: return "XW";
        case PF_R | PF_W: return "RW";
        case PF_R | PF_W | PF_X: return "RWX";
        default: return "UNKOWN";
    }
}

static const char *elfhdr_template[] = {
    "Type: %x",
    "Machine: %x",
    "Version: %x",
    "Entry Point addr: %p",
    "program headers offset: %lu",
    "Section headers offset: %lu",
    "Flags: 0x%x",
    "ELF header size: %u",
    "Program header size: %u",
    "Section header size: %u",
    "Program header num: %u",
    "Section header num: %u",
    "Section header string table index: %u"
};

size_t compose_template(char *buff, size_t size)
{
    size_t offset = 0;
    for (int i = 0; i < elfhdr_fieds_num - 1; ++i) {
        strcpy(buff + offset, elfhdr_template[i]);
        offset += strlen(elfhdr_template[i]);
        buff[offset] = '\n';
        offset += 1;
    }
    --offset;
    assert(offset <= size);
    return offset;
}

int check_elfhdr(const Elf64_Ehdr *elfhdr)
{
    return TRUE;
}

void disp_elfhdr(const Elf64_Ehdr *elfhdr)
{
    fprintf(stdout, "ELF Header:\n");
    char buff[512] = {};

    // display elf magic number
    fprintf(stdout, "Magic: ");
    for (int i = 0; i < EI_NIDENT; ++i)
        fprintf(stdout, "%02x ", elfhdr->e_ident[i]);
    fprintf(stdout, "\n");

    // display other fields
    compose_template(buff, 512);
    fprintf(stdout, buff,
            elfhdr->e_type, elfhdr->e_machine,
            elfhdr->e_version, elfhdr->e_entry,
            elfhdr->e_phoff, elfhdr->e_shoff,
            elfhdr->e_flags, elfhdr->e_ehsize,
            elfhdr->e_phentsize, elfhdr->e_shentsize,
            elfhdr->e_phnum, elfhdr->e_shnum,
            elfhdr->e_shstrndx);
    fprintf(stdout, "\n");
}

void disp_section(const Elf64_Shdr *sechdr,
        const char *strtab_buf, size_t buf_size)
{
    assert(sechdr->sh_name < buf_size);
    fprintf(stdout, "name: %18s  ", strtab_buf + sechdr->sh_name);
    fprintf(stdout, "type: %10s  ", SECTION_TYPE_MAP(sechdr->sh_type) + 4);
    fprintf(stdout, "flags: %03lu  ", sechdr->sh_flags);
    fprintf(stdout, "addr: %08lx  ", sechdr->sh_addr);
    fprintf(stdout, "section off: %08lx  ", sechdr->sh_offset);
    fprintf(stdout, "section size: %04lx  ", sechdr->sh_size);
    fprintf(stdout, "entry size: %04lx  ", sechdr->sh_entsize);
}

void disp_strtab(const char *buff, size_t size)
{
    printf("String table\n");
    for (int st = 0; st < size; st++) {
        printf("%s\n", buff+st);
        st += strlen(buff+st);
    }
}

void disp_symtab(plist_t symtab)
{
    assert(symtab);
    fprintf(stdout, "Section headrs:\n");
    pnode_t cur;
    FOR_EACH(symtab, cur) {
        Elf64_Sym *tmp = cur->item;
        fprintf(stdout, "name: %04u  ", tmp->st_name);
        fprintf(stdout, "info: %04d  ", tmp->st_info);
        fprintf(stdout, "other: %04d  ", tmp->st_other);
        fprintf(stdout, "index: %05u  ", tmp->st_shndx);
        fprintf(stdout, "value: %08lx  ", tmp->st_value);
        fprintf(stdout, "size: %08lx  ", tmp->st_size);
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void disp_sechdr(int fd, const Elf64_Ehdr *elfhdr,
        struct list_head *section_list)
{
    fprintf(stdout, "Section headrs:\n");

    // get string table
    Elf64_Shdr *strtab = NULL;
    const size_t buff_size = 4096;
    char strtab_buff[buff_size];
    off_t off;
    size_t size;
    pnode_t cur;
    cur = list_get(section_list, elfhdr->e_shstrndx);
    assert(cur != TAIL(section_list));
    strtab = (Elf64_Shdr*)cur->item;
    off = strtab->sh_offset;
    size = strtab->sh_size;
    assert(size < buff_size);
    lseek(fd, off, SEEK_SET);
    read(fd, strtab_buff, size);

    // iter all list item
    FOR_EACH(section_list, cur) {
        disp_section((Elf64_Shdr *)(cur->item), strtab_buff, 4096);
        fprintf(stdout, "\n");
    }

    // relocate fd to off 0
    lseek(fd, 0, SEEK_SET);
    fprintf(stdout, "\n");
}


void disp_prohdr(struct list_head *prohdr)
{
    fprintf(stdout, "Program headrs:\n");

    pnode_t cur;
    FOR_EACH(prohdr, cur) {
        Elf64_Phdr *tmp = cur->item;
        fprintf(stdout, "type: %18s  ",
                get_prog_seg_type(tmp->p_type));
        fprintf(stdout, "flags: %4s  ",
                get_prog_seg_flags(tmp->p_flags));
        fprintf(stdout, "offset: %08lx  ", tmp->p_offset);
        fprintf(stdout, "vaddr: %08lx  ", tmp->p_vaddr);
        fprintf(stdout, "paddr: %08lx  ", tmp->p_paddr);
        fprintf(stdout, "file size: %08lx  ", tmp->p_filesz);
        fprintf(stdout, "mem size: %08lx  ", tmp->p_memsz);
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");
}

void disp_seg_mapping()
{

}

Elf64_Ehdr *read_elfhdr(int fd)
{
    assert(fd > 0);
    size_t size;
    Elf64_Ehdr *elfhdr;
    // elf header size 256 bytes
    elfhdr = (Elf64_Ehdr*) malloc(DEFAULT_ELF_HEADER_SIZE);
    size = read(fd, (char *)elfhdr, DEFAULT_ELF_HEADER_SIZE);
    assert(size == DEFAULT_ELF_HEADER_SIZE);
    //restore
    size = lseek(fd, 0, SEEK_SET);
    assert(size != ((off_t) - 1));

    return elfhdr;
}

struct list_head *read_sechdr(int fd, const Elf64_Ehdr *elfhdr)
{
    assert(fd > 0);

    size_t total_size, size, nums;
    off_t start, off;
    char buff[4096] = {};
    struct list_head *list = NULL;

    size = elfhdr->e_shentsize;
    nums = elfhdr->e_shnum;
    start = elfhdr->e_shoff;
    total_size = nums * size;
    assert(total_size < (4096));

    lseek(fd, start, SEEK_SET);
    read(fd, buff, total_size);

    printf("[init buf start]: %p\n", buff);
    printf("[init buf end]: %p\n", buff + total_size);
    list_init_by_buff(&list, buff, total_size, size);

    lseek(fd, 0, SEEK_SET);

    return list;
}

struct list_head *read_prohdr(int fd, const Elf64_Ehdr *elfhdr)
{
    off_t off;
    size_t size, nums, total_size;
    char buff[0x1000] = {};
    struct list_head *list, *cur;

    off = elfhdr->e_phoff;
    size = elfhdr->e_phentsize;
    nums = elfhdr->e_phnum;
    total_size = nums * size;
    assert(total_size < 0x1000);

    lseek(fd, off, SEEK_SET);
    read(fd, buff, total_size);

    list_init_by_buff(&list, buff, total_size, size);

    return list;
}

struct list_head *read_symtab(int fd, struct list_head *sechdr)
{
    fprintf(stdout, "Symbol table:\n");
    assert(fd > 0);
    assert(sechdr != NULL);

    struct list_head *list;
    pnode_t cur;
    Elf64_Shdr *symtab_info;
    off_t off;
    size_t total_size, entry_size;
    uint32_t nums;

    // find symtab section
    FOR_EACH(sechdr, cur) {
        Elf64_Shdr *syment = cur->item;
        if (syment->sh_type == SHT_SYMTAB)
            break;
    }
    if (cur == TAIL(sechdr))
        return NULL;

    // get symtab info
    symtab_info = cur->item;
    off = symtab_info->sh_offset;
    total_size = symtab_info->sh_size;
    entry_size = symtab_info->sh_entsize;
    assert(total_size > 0);
    nums = total_size / entry_size;
    fprintf(stdout, "offset: %lu\nsize: %lu\nnums:%u\n",
            off, total_size, nums);

    // allocate list
    char buff[0x1000] = {};
    lseek(fd, off, SEEK_SET);
    read(fd, buff, total_size);

    list_init_by_buff(&list, buff, total_size, entry_size);

    return list;
}

int main()
{
    int fd;
    Elf64_Ehdr *elfhdr;

    struct list_head *sechdr;
    struct list_head *prohdr;
    struct list_head *symtab;
    // struct list_head *strtab;

    const char *filename = "a.out";

    fd = open(filename, O_RDONLY);
    assert(fd > 0);

    elfhdr = read_elfhdr(fd);
    sechdr = read_sechdr(fd, elfhdr);
    getchar();
    prohdr = read_prohdr(fd, elfhdr);
    // strtab = read_strtab(fd, elfhdr);
    symtab = read_symtab(fd, sechdr);


    disp_elfhdr(elfhdr);
    disp_sechdr(fd, elfhdr, sechdr);
    disp_prohdr(prohdr);
    disp_symtab(symtab);

    list_free(&sechdr);
    list_free(&prohdr);
    list_free(&symtab);

    free(elfhdr);

    close (fd);

    return 0;
}
