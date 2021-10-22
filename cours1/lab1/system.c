// lookup the system function in the manual & implement your own function ( void mySystem(char *cmd) ).
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


void mySystem();
int main() {
        char* cmd;

        printf("CMD :");
        scanf("%s",&*cmd); // on get la cmd de l'utilisateur
        mySystem(cmd); // on appel la fonction mySystem

        return 0;
}

void mySystem(char *cmd)
{
        execl("/bin/sh", "sh", "-c", cmd, (char *) NULL); // on exec la cmd shell
}
