#define MAX 1024
#define PRINTF(GDBG,FMT,...) do{ if(GDBG) printf(" %s %d\t " #FMT "\n",\
																__FILE__,__LINE__,##__VA_ARGS__);\
															 }while(0);

typedef struct libList{
	char libname[1024];
	char type[10];
	int libcnt;
}libList;

void abidetail(libList * fn);

