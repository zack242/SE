#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include<fcntl.h>

sem_t *s1,*s2;

void * f1(void *arg) {

  int *x = (int *)arg;
  sem_wait(s1);
  (*x)++;
  sem_post(s2);
  pthread_exit(NULL);
}

void * f2(void *arg) {
  int *x = (int *)arg;

  sem_wait(s2);
  (*x)--;
  sem_post(s1);
  pthread_exit(NULL);
}

int main() {
  int i=65;

  s1 = sem_open("/mysem1", O_CREAT, 0644,0);
  s2 = sem_open("/mysem2", O_CREAT, 0645,1);

  int *ptr,*ptr1;
  pthread_t thread1,thread2;

  pthread_create(&thread1, NULL, f1,&i);
  //sleep(1);
  pthread_create(&thread2, NULL, f2,&i);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("%d\n",i);

  sem_unlink("/mysem1");
  sem_unlink("/mysem2");

}
