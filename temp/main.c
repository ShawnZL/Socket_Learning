#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sd;
    FILE *fp;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;
    if (argc != 3) {
        exit(1);
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htonl(atoi(argv[2]));

    connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    
}
void error_handling(char *messgae) {
    fputs(messgae, stderr);
    fputc('\n', stderr);
    exit(1);
}