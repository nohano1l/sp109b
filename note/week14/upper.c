#include <stdio.h>
#include <ctype.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        if (islower(c)) c=toupper(c); //轉成大寫
        if (putchar(c) == EOF) printf("output error!");
        if (c=='\n') fflush(stdout);  //清除緩衝
    }
}
