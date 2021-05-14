#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int mysystem(char *arg[]) {
  if (fork()==0) {   //fork出子行程跑ls -l
    execvp(arg[0], arg); // child : exec("ls -l")
  }
  int status;
  wait(&status);   //等待子行程結束
}

int main() {
  char *arg[] = {"ls", "-l", NULL };
  mysystem(arg);
  printf("main end!\n");
}
