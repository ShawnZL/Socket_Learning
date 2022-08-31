#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();// 复制节点，父子节点分开

    if (pid == 0) // if Child process
        puts("Hi, I`m a child process");
    else {
        printf("Child process ID: %d\n", pid);
        sleep(30);
    }

    if (pid == 0)
        printf("End child process");
    else
        printf("End parent process");
    return 0;
}