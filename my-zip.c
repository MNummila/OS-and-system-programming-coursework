/*
esimerkkiä katsottu osoitteesta
https://stackoverflow.com/questions/20176338/rle-compression-algorithm-c

tekijä: Mikko Nummila
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char *argv[]){
    char current;
    char next;
    int count = 0;
//check for arguments
    if(argc == 1){
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    for(int i = 1; i <argc; i++){
        FILE *source;
	//check if file can be opened
        if((source = fopen(argv[i],"r"))== NULL){
            printf("my-zip: cannot open file\n");
            exit(1);
            }
        while(1){//loop reading chars as long as there are chars
            int u = (fread(&current, sizeof(char), 1, source) == 0);

            if(u||next!=current){
		if(count>0){
		//if char changes write it to file nad its count
			char str[100];
			int dig = sprintf(str,"%d", count);
			
			fwrite(&str,sizeof(char)*dig,1,stdout);
			
	                fwrite(&next,sizeof(char),1,stdout);
			
		}
		//otherwise increase counter
                next = current;
                count = 1;
            }
            else count++;
	// if nothing to read break loop
            if(u)
                break;
      
        }

        fclose(source);
	}
    return (0);
}