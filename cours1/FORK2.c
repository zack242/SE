#include <stdio.h>
#include <unistd.h>

int main(){

        int k = 5;

        for (int i = 0; i < 3; i++) {

                if(fork() == 0)
                {
                        printf("I'm the child \n");
                        k++;
                }
                else
                {
                        printf("I'm the parent \n");
                }
                //printf("-----%d-----\n",i);
                printf("[enfant]:%d --- [parent]:%d \n",getpid(),getppid());

        }
        printf("%d\n",k);
}
