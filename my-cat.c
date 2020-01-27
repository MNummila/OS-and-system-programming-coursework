/*
tekijä: Mikko Nummila
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc ,char *argv[]){
	char buffer[500];
//check for arguments
  	if(argc == 1){
    	return 0;
  	}
	//loop reading and printing as long as there are arguments/files
  	for(int i = 1; i <argc; i++){
  		FILE *fp = fopen(argv[i],"r");
  		if(fp == NULL){//check if file can be opened
  			printf("my-cat: cannot open file\n");
  			exit(1);
  		}
		//read file and print it
  		while(fgets(buffer, 500, fp) != NULL){
  			printf("%s",buffer);
  		}
  		fclose(fp);
  	}
  	return (0);
}