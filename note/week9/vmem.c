#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("location of code : %p\n", main);
    printf("location of heap : %p\n", malloc(100e6));  //分配100*10^6 byte 輸出存取malloc的起始位置
    int x = 3;
    printf("location of stack: %p\n", &x);
    return 0;
}
