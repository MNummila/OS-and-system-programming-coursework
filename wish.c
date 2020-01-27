
/*
Mallia katsottu seuraavista lähteistä

https://brennan.io/2015/01/16/write-a-shell-in-c/
https://www.geeksforgeeks.org/making-linux-shell-c/
https://stackoverflow.com/questions/2218290/concatenate-char-array-in-c

tekijä: Mikko Nummila

built-in command path ei toimi 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define WHITESPACE " \t\r\n\a"

char **parsing(char *buffer);
int launch(char **arguments);
int execute(char **arguments);
char *read_line(void);
int wish_exit(char **arguments);
int wish_cd(char **arguments);
int wish_path(char **arguments);

//list of built-in commands
char *builtin[] = {"exit","cd","path"};
int (*builtin_func[]) (char **) = {&wish_exit,&wish_cd,&wish_path};
//current path
char *paths[] = {"/bin/"};

int main(int argc, char **argv[]){
	char *buffer;
	char **arguments;
	int status;
//shell basic loop
	while(status){
		printf("wish> ");
		buffer = read_line();
		arguments = parsing(buffer);
		status = execute(arguments);
		

		free(buffer);
		free(arguments);
		
	}
	return (0);
}
//built-in path
int wish_path(char **arguments){
	printf("%s\n",paths[0]);
	printf("%s\n",arguments[1]);
	//paths[0] = realloc(paths[],sizeof(arguments[1]));
	paths[0]=arguments[1];
	//*paths[i]=*arguments[i];
	printf("%s\n",paths[0]);
}

int execute(char **arguments){
	int i;
	if(arguments[0]==NULL){	//check if empty
		return 1;
	}
	for(i = 0; i<3;i++){	//check for built-in commands
		if(strcmp(arguments[0],builtin[i])==0){
			return (*builtin_func[i])(arguments);
		}
	}
	//send command to be launched
	return launch(arguments);
}
//built-in cd
int wish_cd(char **arguments){
//check given arguments
	if(arguments[1] == NULL){
		fprintf(stderr,"No argument\n");
	}
	else if(arguments[2] != NULL){
		fprintf(stderr,"Too many arguments\n");
	} else {
		//change dir
		if(chdir(arguments[1]) != 0){
			perror("cd error");
		}
	}
	return 1;

}
//built-in exit
int wish_exit(char **arguments){
	exit(0);
}

char **parsing(char *buffer){
	char **arguments = malloc(100 * sizeof(char*));	
	char *words;
	int i = 0;
//separate arguments, add them to array and return pointer to array
	words = strtok(buffer,WHITESPACE);
	while(words != NULL){
		arguments[i] = words;
		i++;

		words = strtok(NULL,WHITESPACE);
	}
	arguments[i] = NULL;

	return arguments;
}

//reads input and returns pointer to buffer
char *read_line(void){
	char *buffer;
	size_t buffersize = 500;

	buffer = (char*)malloc(buffersize * sizeof(char));
	getline(&buffer,&buffersize,stdin);
	return buffer;
}


int launch(char **arguments){
	int status;
	char *p;
	//combine path and command
	p = malloc(strlen(paths[0])+1+4);
	strcpy(p, paths[0]);
	strcat(p, arguments[0]);
	pid_t pid = fork();
	//check if fork failed
    if (pid == -1) { 
        printf("Fork failed\n"); 
        return 1;
	//execute command unless it failed
    } else if (pid == 0) { 
        if (execv(&p[0], arguments) < 0) { 
            printf("Exec failed\n"); 
        } 
        exit(0); 
    } else { 
        //waiting for child
        wait(NULL);
	free(p); 
        return 1; 
    } 
} 