#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]) {
    int fds[2];
    char str[] = "Who are you";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork(); //复制用于管道 I/O 的文件描述符，此时父子进程同时拥有I/O文件描述符
    if (pid == 0)
    {
        write(fds[1], str, sizeof(str)); // 子进程向里边传输字节符
    }
    else
    {
        read(fds[0], buf, BUF_SIZE); // 父进程从里边读取字节符号
        puts(buf);
    }
    return 0;
}
