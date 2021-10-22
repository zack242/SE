#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {


        if(fork()==0) // Lance un premier processus fils
        {
                printf("I'm the child one\n");
        }
        else
        {
              if(fork()==0) // Lance un deuxieme processus fils
                {
                        printf("I m the child two \n");
                        if(fork()==0) // Lance un troisieme processus
                        printf("I'm the child of the child\n");

                }else{
                        printf("I'm the parents\n");
                }
        }

}
