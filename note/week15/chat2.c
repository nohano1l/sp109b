#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SMAX 80

int main(int argc, char *argv[]) {
    int id = argv[1][0]-'0';
    int fd = open("chat.dat", O_RDWR | O_CREAT); //建立檔案
    char *buf = mmap(NULL, 2*SMAX, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); //把fd映射在記憶體上
    char *myMsg, *yourMsg; //記憶體中的位址
    //共用記憶體 //如果輸入超過80byte(SMAX)會有問題
    if (id == 0) {
        myMsg = buf;
        yourMsg = buf + SMAX;
    } else {
        myMsg = buf + SMAX;
        yourMsg = buf;
    }
    if (fork() == 0) {
        // child: receive message and print
        while (1) { //子行程
            if (yourMsg[0] != '\0') {
                printf("receive: %s", yourMsg); //印出
                yourMsg[0] = '\0';
            }
        }
    } else { //父行程
        // parent: readline and put into myMsg in buf
        while (1) {
            fgets(myMsg, SMAX, stdin); //送出
        }
    }
    munmap(buf, 2*SMAX); //關閉映射
    close(fd); //關閉檔案
    return 0;
}
