#include <stdio.h>
#include <unistd.h>

int main(){

        int k = 5;

        for (int i = 0; i < 1; i++) {

                if(fork() == 0)
                {
                        printf("I'm the child \n");
                      //  char *args[]={"/Users/zack/dev/SE/cours1/execHello",NULL};
                        char *args[]={"/Users/zack/Downloads/rar/rar",NULL};
                        execv(args[0],args);
                        k++;
                        printf("%d\n",k );
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
