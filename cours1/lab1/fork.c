#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	int id = fork(); // on appel la fonction fork pour cree un procesus enfant
	if (id == 0) { //fork()==0 veut dire que on est dans le process enfant
    printf("I'm the child !\n");
		printf("pid:%d - ppid:%d \n", getpid(),	getppid());
	} else { // fork >0 on est dans le process parent et <0 erreur dans l'appel de fork
		printf("I'm the parent !\n");
		printf("pid:%d - ppid:%d \n", getpid(), id);
	}
}
