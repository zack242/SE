#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void * f1(void *arg) {
  int *x = (int *)arg;
  (*x)++;
  pthread_exit(NULL);
}

void * f2(void *arg) {
  int *x = (int *)arg;
  (*x)--;
  pthread_exit(NULL);
}

int main() {
  pthread_t thread1,thread2;
  int *ptr,*ptr1;
  int i=65;

  pthread_create(&thread2, NULL, f2,&i);
  sleep(1);
  pthread_create(&thread1, NULL, f1,&i);


  printf("%d\n",i);

}
