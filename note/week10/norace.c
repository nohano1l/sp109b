#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;   //定義初始值
#define LOOPS 100000
int counter = 0;

void *inc()
{
  for (int i=0; i<LOOPS; i++) {
    pthread_mutex_lock( &mutex1 );   // 上鎖、避免競爭情況
    counter = counter + 1;           // 臨界區間、修改共用變數中
    pthread_mutex_unlock( &mutex1 ); // 變數修改完畢，解鎖
  }
  return NULL;
}

void *dec()
{
  for (int i=0; i<LOOPS; i++) {
    pthread_mutex_lock( &mutex1 );   // 上鎖、避免競爭情況
    counter = counter - 1;           // 臨界區間、修改共用變數中
    pthread_mutex_unlock( &mutex1 ); // 變數修改完畢，解鎖
  }
  return NULL;
}


int main() 
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, inc, NULL);
  pthread_create(&thread2, NULL, dec, NULL);

  pthread_join( thread1, NULL);     //thread1執行完才會通過
  pthread_join( thread2, NULL);
  printf("counter=%d\n", counter);
}