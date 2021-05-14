#include <stdio.h>
#include <unistd.h>

int main() {
  char *arg[] = {"ls", "-l", NULL };
  printf("execvp():before\n");
  execvp(arg[0], arg);   //替換成ls -l
  printf("execvp():after\n");   //故不會執行此段
}
