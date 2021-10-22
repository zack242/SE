#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include<fcntl.h>

sem_t *r1,*r2,*r3;

void * f1(void *arg) {

  sem_wait(r3);
  sleep(1);
  printf("--1\n");
  sem_post(r1);
  pthread_exit(NULL);

}
void * f2(void *arg) {

  sem_wait(r1);
  sleep(1);
  printf("--2\n");
  sem_post(r2);
  pthread_exit(NULL);
}
void * f3(void *arg) {

  sem_wait(r2);
  sleep(1);
  printf("--3\n");
  sem_post(r3);
  pthread_exit(NULL);
}

//

int main() {

  r1 = sem_open("/mysem4",O_CREAT, 0632,0);
  r2 = sem_open("/mysem5",O_CREAT, 0651,0);
  r3 = sem_open("/mysem6",O_CREAT, 0652,0);

  int *ptr,*ptr1,*ptr2;
  pthread_t thread1,thread2,thread3;


  pthread_create(&thread1, NULL, f1,NULL);
  pthread_create(&thread2, NULL, f2,NULL);
  pthread_create(&thread3, NULL, f3,NULL);


    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

}
