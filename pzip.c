/*
esimerkkiä katsottu osoitteista

https://stackoverflow.com/questions/20176338/rle-compression-algorithm-c

https://www.geeksforgeeks.org/multithreading-c-2/

tekijä: Mikko Nummila
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <pthread.h>

void *compress(void *arg);

int main(int argc ,char *argv[]){
//check available cores
	int cores = get_nprocs();
	pthread_t th;
//check for arguments
    if(argc == 1){
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
//do this if no need to loop since there are enough cores
	if(cores >= argc-1){
	//create threads based on number of arguments
		for(int i = 1; i < argc; i++){
			pthread_create(&th, NULL, compress, argv[i]);
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
				pthread_create(&th, NULL, compress, argv[u]);
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

void *compress(void *arg){
	char current;
    char next;
    int count = 0;
        FILE *source;
	//check if file can be opened
        if((source = fopen(arg,"r"))== NULL){
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
	return NULL;
}