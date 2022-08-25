#include <stdio.h> //standard input & output
#include <stdlib.h> //standard library
#include <string.h>
#include <ctype.h>
#include <unistd.h> // 系统封装调用
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum, int opnds[], char operator);
int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    int recv_len, recv_cnt;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt, i;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    // 创建套接字
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY 表示服务器上所有网卡
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);

    for (i = 0; i < 1; ++i) {
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
        read(clnt_sock, &opnd_cnt, 1); // 统计个数

        recv_len = 0;
        while ((opnd_cnt*OPSZ+1) > recv_len) {
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
            recv_len += recv_cnt;
        }
        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
        write(clnt_sock, (char*)&result, sizeof(result));
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

int calculate(int opnum, int opnds[], char op) {
    int result = opnds[0], i;
    switch(op)
    {
        case '+':
            for (i = 1; i < opnum; ++i) result += opnds[i];
            break;
        case '-':
            for (i = 1; i < opnum; ++i) result -= opnds[i];
            break;
        case '*':
            for (i = 1; i < opnum; ++i) result *= opnds[i];
            break;
    }
    return result;
}

void error_handling(char *messgae) {
    fputs(messgae, stderr); // write string into stream 将string写入stderr中
    fputc('\n', stderr); // write char into stream 将char写入输出流当中
    exit(1); // exit(0) 正常输出 exit(-1/1)非正常
}
