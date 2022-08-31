#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
void error_handling(char *message);
int main() {
    int sock;
    int snd_buf = 1024*3, rev_buf = 1024 * 3, state;
    socklen_t len;

    sock = socket(PF_INET, SOCK_STREAM, 0);// tcp
    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&rev_buf, sizeof(rev_buf));
    // 第一个返回信息就是我们应该给予缓冲区大小的大小
    if (state)
        error_handling("setsockopt() error");

    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&snd_buf, sizeof(snd_buf));
    if (state)
        error_handling("setsockopt1() error");
    len = sizeof(snd_buf);
    state= getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
    if (state)
        error_handling("getsockopt() error");
    len = sizeof(rev_buf);
    state= getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rev_buf, &len);
    if (state)
        error_handling("getsockopt() error");
    printf("Input buffer size: %d \n", rev_buf);
    printf("Output buffer size: %d \n", snd_buf);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
}
