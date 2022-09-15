/*
#include <unistd.h>
#include <stdio.h>
#include <sys/epoll.h>
int main() {
    int epfd, nfds;
    char buf[256];
    struct epoll_event event, events[5];
    epfd=epoll_create(1);
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN; //LT默认模式
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO, &event);
    while (1) {
        nfds = epoll_wait(epfd, events, 5, -1);
        int i;
        for (i = 0; i < nfds; ++i) {
            if (events[i].data.fd == STDIN_FILENO);
            //read(STDIN_FILENO, buf, sizeof(buf));
            printf("hello world\n");
        }
    }
    return 0;
}
*/

/*
//阻塞I/O
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
// 阻塞I/O
int main() {
    char buf[10];
    int len;
    while(1) {
        // STDIN_FILENO 是标准输入的描述符，它的值是 0. STDOUT_FILENO 是标准输出的描述符，它的值是 1.
        len = read(STDIN_FILENO, buf, 10);
        write(STDOUT_FILENO, buf, len );
        printf("read write successful \n");
    }
    return 0;
}
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
// 非阻塞I/O
int main() {
    char buf[10];
    int len;
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);	// 设置为非阻塞形式

    while(1) {
        // STDIN_FILENO 是标准输入的描述符，它的值是 0. STDOUT_FILENO 是标准输出的描述符，它的值是 1.
        len = read(STDIN_FILENO, buf, 10);
        write(STDOUT_FILENO, buf, len );
        printf("read write successful \n");
    }
    return 0;
}
