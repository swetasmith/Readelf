/*
 * Print the ELF Executable Header from an ELF object.
 *
 * $Id$
 */

#include <err.h>
#include <fcntl.h>
#include <gelf.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <bsd/vis.h>
#include "liblist.h"
void abidetail(char * fn)
{
    int i, fd;
    Elf *e;
    char *id, bytes[5];
    size_t n;
    GElf_Ehdr ehdr; 

    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EXIT_FAILURE, "ELF library initialization "
            "failed: %s", elf_errmsg(-1));

    if ((fd = open(fn, O_RDONLY, 0)) < 0)
        err(EXIT_FAILURE, "open \"%s\" failed", fn);

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        errx(EXIT_FAILURE, "elf_begin() failed: %s.",elf_errmsg(-1));
#if 0
    if (elf_kind(e) != ELF_K_ELF)
        errx(EXIT_FAILURE, "\"%s\" is not an ELF object.",fn);
#endif
    if (gelf_getehdr(e, &ehdr) == NULL) 
        errx(EXIT_FAILURE, "getehdr() failed: %s.",elf_errmsg(-1));
		
		switch(ehdr.e_machine){
			case 0x02:
				printf("SPARC\n");
				break;
			case 0x03:
				printf("x86\n");
				break;
			case 0x08:
				printf("MIPS\n");
				break;
			case 0x14:
				printf("PPC\n");
				break;
			case 0x16:
				printf("S390\n");
				break;
			case 0x28:
				printf("ARM\n");
				break;
			case 0x2A:
				printf("SuperH\n");
				break;
			case 0x32:
				printf("IA-64\n");
				break;
			case 0x3E:
				printf("x86-64\n");
				break;
			case 0xB7:
				printf("AArch64\n");
				break;
			case 0xF3:
				printf("RISC-V\n");
				break;
		}

    (void) elf_end(e);
    (void) close(fd);
    exit(EXIT_SUCCESS);
}

#if 0
int
main(int argc, char **argv)
{
    int i, fd;
    Elf *e;
    char *id, bytes[5];
    size_t n;
    GElf_Ehdr ehdr; 

    if (argc != 2)
        errx(EXIT_FAILURE, "usage: %s file-name", argv[0]);

    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EXIT_FAILURE, "ELF library initialization "
            "failed: %s", elf_errmsg(-1));

    if ((fd = open(argv[1], O_RDONLY, 0)) < 0)
        err(EXIT_FAILURE, "open \"%s\" failed", argv[1]);

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        errx(EXIT_FAILURE, "elf_begin() failed: %s.",
            elf_errmsg(-1));

    if (elf_kind(e) != ELF_K_ELF)
        errx(EXIT_FAILURE, "\"%s\" is not an ELF object.",
            argv[1]);

    if (gelf_getehdr(e, &ehdr) == NULL) 
        errx(EXIT_FAILURE, "getehdr() failed: %s.",
            elf_errmsg(-1));
#if 0
    if ((i = gelf_getclass(e)) == ELFCLASSNONE) 
        errx(EXIT_FAILURE, "getclass() failed: %s.",
            elf_errmsg(-1));
#endif
		switch(ehdr.e_machine){
			case 0x02:
				printf("SPARC\n");
				break;
			case 0x03:
				printf("x86\n");
				break;
			case 0x08:
				printf("MIPS\n");
				break;
			case 0x14:
				printf("PPC\n");
				break;
			case 0x16:
				printf("S390\n");
				break;
			case 0x28:
				printf("ARM\n");
				break;
			case 0x2A:
				printf("SuperH\n");
				break;
			case 0x32:
				printf("IA-64\n");
				break;
			case 0x3E:
				printf("x86-64\n");
				break;
			case 0xB7:
				printf("AArch64\n");
				break;
			case 0xF3:
				printf("RISC-V\n");
				break;
		}

    (void) elf_end(e);
    (void) close(fd);
    exit(EXIT_SUCCESS);
}
#endif
