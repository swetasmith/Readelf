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
#include <string.h>
#include <unistd.h>
#include <bsd/vis.h>
#include "liblist.h"
extern int debug;


void abidetail(libList * fn)
{
    int i;
		int  fd;
    Elf *e;
//  char *id, bytes[5];
    //size_t n;
    GElf_Ehdr ehdr; 
		//PRINTF(debug,%s,fn);
    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EXIT_FAILURE, "ELF library initialization " "failed: %s", elf_errmsg(-1));

    if ((fd = open(fn->libname, O_RDONLY, 0)) < 0)
        err(EXIT_FAILURE, "open \"%s\" failed", fn->libname);

    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        errx(EXIT_FAILURE, "elf_begin() failed: %s.",elf_errmsg(-1));
   
	 //	PRINTF(debug, %d ,elf_kind(e)); 
		if (elf_kind(e) != ELF_K_ELF)
       errx(EXIT_FAILURE, "\"%s\" is not an ELF object.",fn->libname);
    
		if (gelf_getehdr(e, &ehdr) == NULL) 
        errx(EXIT_FAILURE, "getehdr() failed: %s.",elf_errmsg(-1));
    
		if ((i = gelf_getclass(e)) == ELFCLASSNONE) 
        errx(EXIT_FAILURE, "getclass() failed: %s.",elf_errmsg(-1));
		PRINTF(debug, Object FileName: %s Elf_kind_number: %d  Machine Type: %d,fn->libname,elf_kind(e),ehdr.e_machine);

		switch(ehdr.e_machine){
			case 0x02:
				PRINTF(debug,SPARC);
				strcpy(fn->type,"SPARC");
				break;
			case 0x03:
				PRINTF(debug,x86);
				strcpy(fn->type,"x86");
				break;
			case 0x08:
				PRINTF(debug,MIPS);
				strcpy(fn->type,"MIPS");
				break;
			case 0x14:
				PRINTF(debug,PPC);
				strcpy(fn->type,"PPC");
				break;
			case 0x16:
				PRINTF(debug,S390);
				strcpy(fn->type,"S390");
				break;
			case 0x28:
				PRINTF(debug,ARM);
				strcpy(fn->type,"ARM");
				break;
			case 0x2A:
				PRINTF(debug,SuperH);
				strcpy(fn->type,"SuperH");
				break;
			case 0x32:
				PRINTF(debug,IA-64);
				strcpy(fn->type,"IA-64");
				break;
			case 0x3E:
				PRINTF(debug,x86-64);
				strcpy(fn->type,"x86-64");
				break;
			case 0xB7:
				PRINTF(debug,AArch64);
				strcpy(fn->type,"AArch64");
				break;
			case 0xF3:
				PRINTF(debug,RISC-V);
				strcpy(fn->type,"RISC-V");
				break;
			default:
				printf("Something is Wrong here\n");
				break;
		}

    (void) elf_end(e);
    (void) close(fd);
   // exit(EXIT_SUCCESS);
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
