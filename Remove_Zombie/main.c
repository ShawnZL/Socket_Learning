#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig) {
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) { //正常终止
        printf("Removed proc id: %d \n", id);
        printf("Child send: %d \n", WEXITSTATUS(status));// 返回子进程返回值
    }
}

int main(int argc, char *argv[]) {
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask); //该函数的作用是将信号集初始化为空。
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);//子进程终止时会向父进程发送SIGCHLD信号，告知父进程回收自己

    pid = fork();
    if (pid == 0) {// 子进程执行区域
        puts("Hi! I`m child process");
        sleep(10);
        return 12;
    }
    else {//父进程区域
        printf("Child proc id: %d \n", pid);
        pid = fork();
        if (pid == 0) {// 另一个子进程执行区域
            puts("Hi! I`m child process");
            sleep(10);
            return 24;
        }
        else {
            int i;
            printf("Child proc id: %d \n", pid);
            for (i = 0; i < 5; ++i) {
                puts("wait...");
                sleep(5);
            }
        }
    }
    return 0;
}
