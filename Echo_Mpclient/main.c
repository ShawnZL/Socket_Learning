#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char *argv[]) {
    int sock;
    pid_t pid;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    pid = fork();
    if (pid == 0) { //子进程
        write_routine(sock, buf);
    }
    else //父进程
        read_routine(sock, buf);
    close(sock);// 关闭连接
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
}

void write_routine(int sock, char *buf) {
    while(1) {
        fgets(buf, BUF_SIZE, stdin); //读取
        if (!strcmp(buf,"q\n")||!strcmp(buf, "Q\n")) { //相同返回0
            shutdown(sock, SHUT_WR); //关闭写
            return;
        }
        write(sock, buf, BUF_SIZE);
    }
}

void read_routine(int sock, char *buf) {
    while(1) {
        int str_len = read(sock, buf, BUF_SIZE);
        if (str_len == 0)
            return;
        buf[str_len] = 0;//读取完成
        printf("Message from server: %s", buf);
    }
}
