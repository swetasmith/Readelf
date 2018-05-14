// Simple demo for JUnzip library. Needs zlib. Should compile with
// something like gcc junzip_demo.c junzip.c -lz -o junzip.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "junzip.h"
#include "liblist.h"

int debug = 0;
static int ilib = 0;
libList liboutput[MAX];

void updateabiinfo(){
	int i = 0;
	for(i=0;i<ilib;i++){
//				abidetail(liboutput[i].libname);
				abidetail(&liboutput[i]);
	}
}

void display(libList a[]){
	int i = 0;
		printf("===================================================\n");
		printf("Total Number of Libraries: %d\n",ilib);
		printf("===================================================\n");
		printf("File \t\t\t\t\t  ArchType\n");
		printf("==== \t\t\t\t\t ==========\n");
	for(i=0;i<ilib;i++)
	{
		printf("%d  %s\t\t%s\n",(i+1),liboutput[i].libname,liboutput[i].type);

	}
		printf("===================================================\n");
}

int matchPatternFromEnd(char str[],char pat[]){

	int slen = 0;
	int plen = 0;
	int sIdx = 0,j=0;
	slen = strlen(str);
	plen = strlen(pat);
	PRINTF(debug,Src: %s Pat: %s, str, pat);
	if(slen < plen){
			printf("%s %d ERROR slen:%d plen:%d\n",__FILE__,__LINE__,slen,plen);
			return -1;
	}
	sIdx = slen - plen;
			PRINTF(debug,Src: %c Pat: %c,str[sIdx], pat[j]);
		for(j=0;j< plen;j++){
	//		PRINTF(debug,Src: %c, Pat: %c,str[sIdx], pat[j]);
			if(pat[j]==str[sIdx]){ 
					sIdx++;
					continue;
				}else{ 
					return 0;
				}
		}
		PRINTF(debug,Src: %c Pat: %c,str[sIdx], pat[j]);

	if(sIdx==slen){return 1;}
	else{ return 0; }
}

int isFileExists(const char * filename){
	struct stat buf;
	int exist = stat(filename,&buf);
	if (exist == 0 ){
		return 1;
	}else{
		return 0;
	}
}

// Replace this with a function that creates the directory if necessary
// and returns 1 if you want directory support
int makeDirectory(char *dir) {
    int ret =0;
		PRINTF(debug, mkdir(%s)  %d, dir,isFileExists(dir));
		if(!isFileExists(dir)){
			ret = mkdir(dir,ACCESSPERMS);
			if(ret == 0){
   			 return 1;
			}
		}

		return 0;
}

void writeFile(char *filename, void *data, long bytes) {
    FILE *out;
    int i;
		int ret;
    // simplistic directory creation support
    for(i=0; filename[i]; i++) {
        if(filename[i] != '/')
            continue;

        filename[i] = '\0'; // terminate string at this point
				ret = makeDirectory(filename);
        if(1==ret) {
            fprintf(stderr, "Successfully created subdirectory %s!\n", filename);
        }

        filename[i] = '/'; // Put the separator back
    }

    if(!i || filename[i-1] == '/')
        return; // empty filename or directory entry

    out = fopen(filename, "wb");

    if(out != NULL) {
        fwrite(data, 1, bytes, out); // best effort is enough here
        fclose(out);
    } else {
        fprintf(stderr, "Couldn't open %s for writing!\n", filename);
    }
}

int processFile(JZFile *zip) {
    JZFileHeader header;
    char filename[1024];
    unsigned char *data;

    if(jzReadLocalFileHeader(zip, &header, filename, sizeof(filename))) {
        printf("Couldn't read local file header!");
        return -1;
    }

    if((data = (unsigned char *)malloc(header.uncompressedSize)) == NULL) {
        printf("Couldn't allocate memory!");
        return -1;
    }

    PRINTF(debug,%s %d / %d bytes at offset %08X, filename,header.compressedSize, header.uncompressedSize, header.offset);

    if(jzReadData(zip, &header, data) != Z_OK) {
        printf("Couldn't read file data!");
        free(data);
        return -1;
    }

		PRINTF(debug,FileName: %s,filename); 
		if(matchPatternFromEnd(filename,".so")){
				PRINTF(debug,FileName: %s,filename); 
				strcpy(liboutput[ilib].libname,filename);
				liboutput[ilib].libcnt = ilib+1;
				ilib++;

		}

    writeFile(filename, data, header.uncompressedSize);
    free(data);

    return 0;
}

int recordCallback(JZFile *zip, int idx, JZFileHeader *header, char *filename, void *user_data) {
    long offset;

    offset = zip->tell(zip); // store current position

    if(zip->seek(zip, header->offset, SEEK_SET)) {
        printf("Cannot seek in zip file!");
        return 0; // abort
    }

    processFile(zip); // alters file offset

    zip->seek(zip, offset, SEEK_SET); // return to position

    return 1; // continue
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int retval = -1;
    JZEndRecord endRecord;

    JZFile *zip;

    if(argc < 2) {
        puts("Usage: junzip_demo file.zip");
        return -1;
    }

    if(!(fp = fopen(argv[1], "rb"))) {
        printf("Couldn't open \"%s\"!", argv[1]);
        return -1;
    }

    zip = jzfile_from_stdio_file(fp);

    if(jzReadEndRecord(zip, &endRecord)) {
        printf("Couldn't read ZIP file end record.");
        goto endClose;
    }

    if(jzReadCentralDirectory(zip, &endRecord, recordCallback, NULL)) {
        printf("Couldn't read ZIP file central record.");
        goto endClose;
    }

    //Alternative method to go through zip after opening it:
    //while(!processFile(zip)) {}
		updateabiinfo();
		display(liboutput);
    retval = 0;

endClose:
    zip->close(zip);
    return retval;
}
