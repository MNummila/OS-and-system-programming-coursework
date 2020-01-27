/*
esimerkkiä katsottu osoitteista

https://stackoverflow.com/questions/20176338/rle-compression-algorithm-c

https://www.geeksforgeeks.org/multithreading-c-2/

tekijä: Mikko Nummila
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/sysinfo.h>
#include <pthread.h>

void *uncompress(void *arg);

int main(int argc ,char *argv[]){
	int cores = get_nprocs();
	pthread_t th;
//check for arguments
    if(argc == 1){
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
//do this if no need to loop since there are enough cores
	if(cores >= argc-1){
	//create threads based on number of arguments
		for(int i = 1; i < argc; i++){
			pthread_create(&th, NULL, uncompress, argv[i]);
		}
	//join threads based on number of arguments
		for(int i = 1; i < argc; i++){
			pthread_join(th, NULL);
		}
	}
//do this since there is more work than cores so loops are needed
	else if(cores < argc-1){
	//loop for work per core
		for(int i = 1; i < argc; i=i+cores){
		//loop for creating threads
			for(int u = i; u < i+cores; u++){
			//check if arguments end before full loop
				if(argv[u]==NULL){
					break;				
				}
				//create thread
				pthread_create(&th, NULL, uncompress, argv[u]);
			}
		//loop for joining threads
			for(int u = i; u < i+2; u++){
			//check if arguments end before full loop
				if(argv[u]==NULL){
					break;				
				}
				//join thread
				pthread_join(th, NULL);
			}		
		}
	}
    return (0);
}

void *uncompress(void *arg){
    char current;
    char next;
    int count = 0;

    FILE *source;
	//check if file can be opened
	if((source = fopen(arg,"r"))== NULL){
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