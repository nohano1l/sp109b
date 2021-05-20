#include <stdio.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
  while(1) {
    time_t ticks = time(NULL);  //time(NULL)取得目前時間//time_t常整數(1970/1/1到現在的毫秒數)
    printf("%.24s\n", ctime(&ticks));
    sleep(1);
  }
}
