#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

#define SMAX 80

struct msg_t {
    long mtype; // type 指定要哪一種消息, 0:取第一個, >0:消息類型為 type 的第一個, <0:消息類型 <=abs(type) 的第一個。
    char mtext[SMAX];
};

int main(int argc, char *argv[]) {
    int id = argv[1][0]-'0';
    int q0 = msgget((key_t) 1235, 0666|IPC_CREAT); //訊息佇列
    int q1 = msgget((key_t) 1236, 0666|IPC_CREAT);
    int myQ, yourQ;
    if (id == 0) {
        myQ = q0;
        yourQ = q1;
    } else {
        myQ = q1;
        yourQ = q0;
    }
    struct msg_t msg = {.mtype=1};
    // char msg[SMAX];
    if (fork() == 0) { //子行程
        // child: receive message and print
        while (1) {
            msgrcv(yourQ, &msg, SMAX, 0, 0); //從訊息佇列取得訊息
            printf("receive: %s", msg.mtext); //印出
        }
    } else { //父行程
        // parent: readline and put into myMsg in buf
        while (1) {
            fgets(msg.mtext, SMAX, stdin); //讀一行
            msgsnd(myQ, &msg, SMAX, 0); //發送訊息到訊息佇列
        }
    }
    return 0;
}
