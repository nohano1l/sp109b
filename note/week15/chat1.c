// https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SMAX 80

int main(int argc, char *argv[]) {
    int fd;
    char *fifo0 = "/tmp/user0";
    char *fifo1 = "/tmp/user1";
    mkfifo(fifo0, 0666);  //建立具名管道//0666:權限(rwx)
    mkfifo(fifo1, 0666);

    char *me, *you;
    if (strcmp(argv[1], "0")) { // me:0 => you:1
        me = fifo0;
        you = fifo1;
    } else { // me:1 => you:0
        me = fifo1;
        you = fifo0;
    }

    char msg[SMAX];
    if (fork() == 0) {   //子行程
        // child: receive message and print
        fd = open(you, O_RDONLY); //開啟對方管道(只讀)
        while (1) {
            int n = read(fd, msg, sizeof(msg)); //讀取
            if (n <= 0) break;
            printf("receive: %s", msg); //印出
        }
        close(fd); //關閉對方管道
    } else {  //父行程
        // parent: readline and send
        fd = open(me, O_WRONLY); //開啟自己管道(只寫)
        while (1) {
            fgets(msg, SMAX, stdin); //讀一行
            int n = write(fd, msg, strlen(msg)+1); //送出
            if (n<=0) break;
        }
        close(fd); //關閉自己管道
    }
    return 0;
}
