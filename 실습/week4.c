#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 2048
#define PERM 0644

int main(int argc, char *argv[]){
	int fd1, fd2, n;
	char buf[BUFSIZE];

	//input check
	if(argc != 3){
		perror("arg error");
		exit(1);
	}
	//open file
	if((fd1=open(argv[1], O_RDONLY, PERM)) < 0){
		perror("fd1 open err");
		exit(1);
	}
	//creat file but, use open() not creat()
	//check your file mode
	if((fd2=open(argv[2], O_WRONLY|O_CREAT, PERM)) < 0){
		perror("fd2 creat err");
		exit(1);
	}
	//read contents in fd1, copy to fd2
	while((n=read(fd1, buf, BUFSIZE)) > 0){
		write(fd2, buf, n);
	}
	//close
	close(fd1);
	close(fd2);
	
	return 0;
}
