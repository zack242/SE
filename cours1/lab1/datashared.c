#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
        int i = 5;
        if (fork() == 0)
        {
                printf("I'm the child !\n");
                i++;
        } else {
                printf("I'm the parent !\n");
                sleep(3); // sleep for 3 seconds
                printf("%d\n", i); // what happens here ?? Explain
        }
}
