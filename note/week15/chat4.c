#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define SMAX 80

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_DGRAM, 0); //設定環境參數//SOCK_DGRAM無保障
    struct sockaddr_in saddr, raddr;
    memset(&saddr, 0, sizeof(saddr));
    memset(&raddr, 0, sizeof(raddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888);
    char msg[SMAX];
    if (argc==1) { // server
        printf("I am server...\n");
        saddr.sin_addr.s_addr = INADDR_ANY;
        bind(sfd, (struct sockaddr*) &saddr, sizeof(struct sockaddr));
        socklen_t rAddrLen = sizeof(struct sockaddr);
        int rlen = recvfrom(sfd, msg, SMAX, 0, (struct sockaddr*) &raddr, &rAddrLen);
        printf("receive: %s from client addr %s\n", msg, inet_ntoa(raddr.sin_addr));
    } else { // client
        printf("I am client...\n");
        saddr.sin_addr.s_addr = inet_addr(argv[1]);
        memcpy(&raddr, &saddr, sizeof(saddr));
        char *connMsg = "<connect request>";
        sendto(sfd, connMsg, strlen(connMsg)+1, 0, (struct sockaddr*) &saddr, sizeof(struct sockaddr));
    }
    if (fork() == 0) { //子行程
        // child: receive message and print
        while (1) {
            socklen_t rAddrLen = sizeof(struct sockaddr);
            recvfrom(sfd, msg, SMAX, 0, (struct sockaddr*) &raddr, &rAddrLen); //從參數指定的位置(127.0.0.1)接收
            printf("receive: %s", msg); //印出
        }
    } else { //父行程
        // parent: readline and send msg
        while (1) {
            fgets(msg, SMAX, stdin);
            sendto(sfd, msg, strlen(msg)+1, 0, (struct sockaddr*) &raddr, sizeof(struct sockaddr));//傳送到參數指定的位置(127.0.0.1)
        }
    }
    close(sfd); //關閉連線
    return 0;
}
