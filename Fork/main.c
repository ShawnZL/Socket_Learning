#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char *argv[]) {
    pid_t pid;
    int lval = 20;
    gval++; lval += 5;
    // 11 25
    pid = fork(); // 复制节点，父子节点分开
    if (pid == 0) // if Child process
        gval += 2, lval += 2;
    else // if parent process
        gval -= 2, lval -= 2;

    if (pid == 0)
        printf("Child Proc: [%d, %d]\n", gval, lval);
    else
        printf("Parent Proc: [%d %d]\n", gval, lval);
    return 0;
}