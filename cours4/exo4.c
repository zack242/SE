#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t *s1,*s2,*s3;
int *ptr1,*ptr2,*ptr3;
pthread_t thread1,thread2,thread3,thread4;


typedef struct t_data
{
        double val1;
        double val2;

}data;

int checkspot(int tab[3])
{
        for(int i=0; i < 3; i++){
                if(tab[i]==0)
                        return i;
        }
        return -1;
}


void * f1(void *arg) {

        int *a = malloc(sizeof(int));
        struct t_data *args = (struct t_data *) arg;


        *a = args->val1+args->val2;
        sem_post(s1);

        pthread_exit(a);
}

void * f2(void *arg) {

        int *a = malloc(sizeof(int));
        struct t_data *args = (struct t_data *) arg;

        *a = args->val1+args->val2;
        sem_post(s2);

        pthread_exit(a);

}

void * f3(void *arg) {

        int *a = malloc(sizeof(int));
        struct t_data *args = (struct t_data *) arg;

        *a = args->val1+args->val2;
        sem_post(s3);
        pthread_exit(a);
}


void * f4(void *arg)
{

int resultat[3];
int tmp1,tmp2,tmp3,tmp4;

resultat[0]=0;
resultat[1]=0;
resultat[2]=0;

sem_wait(s1);
sem_wait(s2);

pthread_join(thread1, (void **) &ptr1);
pthread_join(thread2, (void **) &ptr2);

tmp1=checkspot(&resultat[0]);
resultat[tmp1]=*ptr1;

tmp2=checkspot(&resultat[0]);
resultat[tmp2]=*ptr2;

tmp3=resultat[tmp2]*resultat[tmp1];

sem_wait(s3);
pthread_join(thread3, (void **) &ptr3);
tmp4=checkspot(&resultat[0]);
resultat[tmp4]=*ptr3;

printf("%d\n",resultat[tmp4]*tmp3);
pthread_exit(NULL);

}


int main() {

        double a=1,b=2,c=3,d=4,e=5,f=6;

        s1 = sem_open("/mysem4",O_CREAT, 0632,1);
        s2 = sem_open("/mysem5",O_CREAT, 0651,1);
        s3 = sem_open("/mysem6",O_CREAT, 0652,1);

        data *arg = malloc(sizeof(struct t_data)*3);

        arg[0].val1=a;
        arg[0].val2=b;
        arg[1].val1=c;
        arg[1].val2=d;
        arg[2].val1=e;
        arg[2].val2=f;

        pthread_create(&thread1, NULL,f1,arg);
        pthread_create(&thread2, NULL,f2,arg+1);
        pthread_create(&thread3, NULL,f3,arg+2);
        pthread_create(&thread4, NULL,f4,NULL);

        pthread_join(thread4,NULL);

        sem_unlink("/mysem4");
        sem_unlink("/mysem5");
        sem_unlink("/mysem6");

}
