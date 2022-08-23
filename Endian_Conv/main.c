#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void error_handling(char * message);
int main(int argc, char *argv[]) {
    /*
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port: %#x \n", host_port);
    printf("Network ordered port: %#x \n", net_port);
    printf("Host ordered address: %#x \n", host_addr);
    printf("Network ordered address: %#x \n", net_addr);
    */
    /*
    // inet_addr 成功返回32大端序整数型值
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";
    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
        printf("Error occured!\n");
    else printf("Network ordered integer addr: %#lx \n", conv_addr);

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
        printf("Error occured!\n");
    else printf("Network ordered integer addr: %#lx \n", conv_addr);

    //inet_aton
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if (!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error");
    else
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr);
    */
    struct sockaddr_in addr1, addr2;
    char * str_ptr;
    char str_arr[20];
    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1: %s \n", str_ptr);

    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n", str_ptr);
    printf("Dotted-Decimal notation3: %s \n", str_arr);

    //
    int serv_sock;
    struct sockaddr_in serv_addr;
    char * serv_port = "9190";

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(serv_port));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(serv_sock, (struct sockaddr * ) &serv_addr, sizeof(serv_addr));
    //
    return 0;
}

void error_handling(char * message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
