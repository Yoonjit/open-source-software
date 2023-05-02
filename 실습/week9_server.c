#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

#define BUF_SIZE 100
void error_handling(char *message);
void backwards(char *message, int str_len);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_un serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    char message[BUF_SIZE];

    serv_sock=socket(AF_INET, SOCK_STREAM, 0); // TODO
    if(serv_sock == -1) error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family=AF_INET; // TODO
    
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) error_handling("bind() error");

    if(listen(serv_sock, 5)==-1) error_handling("listen() error");

    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1) error_handling("accept() error");

    while(1) {
        int str_len = read(clnt_sock, message, BUF_SIZE);
        if(str_len == 0) break;
        backwards(message, str_len);
        write(clnt_sock, message, str_len);
    }

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void backwards(char *message, int str_len){
    char temp;
    int size = str_len/2;
    for(int i = 0; i < size; i++){
        temp = message[i];
        message[i] = message[(str_len-2)-i];
        message[(str_len-2)-i] = temp;
    }
    printf("%s: %d\n", message, str_len-1);
}
