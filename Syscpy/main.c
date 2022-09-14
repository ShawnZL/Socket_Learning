#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 3
int main(int argc, char *argv[]) {

    //基于read&write无缓冲
    int fd1, fd2;
    int len;
    char buf[BUF_SIZE];
    fd1 = open("news.txt", O_RDONLY);
    fd2 = open("cpy.txt", O_WRONLY|O_CREAT|O_TRUNC);

    while ((len = read(fd1, buf, sizeof buf)) > 0) {
        write(fd2, buf, len);
    }
    close(fd1);
    close(fd2);

    /* 使用缓冲
    FILE * fp1;//FILE 结构体指针
    FILE * fp2;
    char buf[BUF_SIZE];

    fp1 = fopen("news.txt", "r");
    fp2 = fopen("cpy.txt", "w");

    while (fgets(buf, BUF_SIZE, fp1) != NULL)
        fputs(buf, fp2);
    fclose(fp1);
    fclose(fp2);
    */
    return 0;
}
