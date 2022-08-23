#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char *message);
// 打开文件与写入文件
int main() {
    int fd;
    char buf[] = "let`s go!\n";

    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
    if (fd ==- 1) // 表示创建失败
        error_handling("open() error!");
    printf("file descriptor: %d \n", fd);

    if (write(fd, buf, sizeof(buf)) == -1)
        error_handling("write() error!");
    close(fd);
    return 0;
}

void error_handling(char *messgae) {
    fputs(messgae, stderr);
    fputc('\n', stderr);
}
