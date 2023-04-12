#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PERM 0644

int main(int argc, char *argv[]){
    pid_t pid;
    if(argc < 3){
        printf("arg error. Please insert the existing file and the target file.\n");
        execlp("ls", "ls", "-al", NULL);
        printf("If this line is printed, there is a problem with execlp().\n");
    }

    if(pid = fork() == 0){
        execlp("cp", "cp", argv[1], argv[2], NULL);
        printf("If this line is printed, there is a problem with execlp().\n");
    }
    wait(NULL);

    if(pid = fork() == 0){
        printf("--------------------------------\n");
        printf("contents of %s\n", argv[1]);
        printf("--------------------------------\n");
        execlp("head", "head", argv[1], NULL);
        printf("If this line is printed, there is a problem with execlp().\n");
    }
    
    wait(NULL);
    printf("--------------------------------\n");
    printf("contents of %s\n", argv[2]);
    printf("--------------------------------\n");
    execlp("head", "head", argv[2], NULL);
    printf("If this line is printed, there is a problem with execlp().\n");
    return 0;
}
