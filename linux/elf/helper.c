#include "helper.h"
#include <fcntl.h>

void elf_init(pelf_t self, const char *filename)
{
    self->fd = open(filename, O_RDONLY);
    assert(self->fd);
}

void elf_read_elfhdr(pelf_t self)
{
    Elf64_Ehdr *hdr = malloc(sizeof(Elf64_Ehdr));
    read(self->fd, hdr, sizeof(Elf64_Ehdr));
    self->elfhdr = hdr;
}

void elf_read_sechdrs(pelf_t self)
{
    assert(self->elfhdr);
    Elf64_Ehdr *elfhdr = self->elfhdr;
    size_t total_size = elfhdr->e_shnum * elfhdr->e_ehsize;

    self->sechdrs = malloc(total_size);
    pread(self->fd, self->sechdrs, total_size, elfhdr->e_shoff);
}

void elf_read_prohdrs(pelf_t self)
{
    Elf64_Ehdr *elfhdr = self->elfhdr;
    size_t total_size = elfhdr->e_phentsize * elfhdr->e_phnum;

    pread(self->fd, self->prohdrs, total_size, elfhdr->e_phoff);
}

void elf_parse(pelf_t self)
{
    self->elf_read_elfhdr(self);
    self->elf_read_sechdrs(self);
    self->elf_read_prohdrs(self);
}

void elf_free(pelf_t self)
{
    close(self->fd);
}
