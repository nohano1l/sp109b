#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SMAX 128

int main() {
  int a = open("a.txt", O_RDWR);   //檔案描述值(整數)
  int b = open("b.txt", O_CREAT|O_RDWR, 0644);  //8進位的參數,6(110rwx)自己的讀取權限,4(100)同一群組的讀取權限,4所有的讀取權限
  char text[SMAX];
  int n = read(a, text, SMAX);
  printf("n=%d\n", n);
  write(b, text, n);
  printf("a=%d, b=%d\n", a, b);
}


