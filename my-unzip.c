/*
esimerkkiä katsottu osoitteesta
https://stackoverflow.com/questions/20176338/rle-compression-algorithm-c

tekijä: Mikko Nummila
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc ,char *argv[]){
    char current;
    char next;
    int count = 0;
//check for arguments
    if(argc == 1){
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
//loop as long there are files
    for(int i = 1; i <argc; i++){
        FILE *source;
        if((source = fopen(argv[i],"r"))== NULL){
            printf("my-unzip: cannot open file\n");
            exit(1);
            }
	//loop as long as there is something to read
        while(fread(&next, sizeof(char), 1, source) != 0){
			//check if number or letter
			int number = atoi(&next);	
			if(number == 0){
				current = next;
				
			}
			if(number != 0){
				count = number;
				
			}
	//when there is number and letter write as many letters as number dictates
			if((count != 0) && (atoi(&next)==0)){
				for(int i = 0; i < count; i++){
					printf("%c",current);
				}
				//reset count variable
				count = 0;
				
			}
        }
        fclose(source);
	}
    return (0);
}