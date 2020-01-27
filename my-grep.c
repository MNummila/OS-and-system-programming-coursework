/*
tekijä: Mikko Nummila
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char *argv[]){
    char buffer[1500];
    char *found;
//check for arguments
    if(argc == 1){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
	//if enough arguments save searchterm
	if(argc == 2){
	  while(fgets(buffer, 1500, stdin) != NULL){
            found = strstr(buffer, argv[1]);
            if(found != NULL){
                printf("%s\n",buffer);
                found = NULL;
            }
      
        }
		
	}
//loop as long there are files
    for(int i = 2; i <argc; i++){
        FILE *fp;
	//check if file can be opened
        if((fp = fopen(argv[i],"r"))== NULL){
            printf("my-grep: cannot open file\n");
            exit(1);
            }
	//loop through file and print current line if searchterm is found
        while(fgets(buffer, 500, fp) != NULL){
            found = strstr(buffer, argv[1]);
            if(found != NULL){
                printf("%s\n",buffer);
                found = NULL;
            }
      
        }
        fclose(fp);
    }
    return (0);
}