#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv)
{
        int id;
        int i=0;
        int *ptr;
        system("ipcs -m");
        id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); system("ipcs -m");
        1
        ptr = (int *) shmat(id, NULL, 0);
        *ptr = 54; i = 54;
        if (fork() == 0) {
                (*ptr)++;
                i++;
                printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i); exit(0);
        } else {
                wait(NULL);
                printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i);
                shmctl(id, IPC_RMID, NULL);
        }
}
