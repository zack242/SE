#include <stdio.h>
#include <stdlib.h>
#define SIZE 65536
typedef short byte_t;
typedef int address_t;


typedef struct
{
        int mem_log[SIZE];
        int vec_log[SIZE];
}mem_t;

mem_t* initMem()
{
        mem_t* mem = malloc(sizeof(mem_t));
        for(int i = 0; i < SIZE; i++)
        {
                mem->mem_log[i] = 0;
                mem->vec_log[i] = 0;
        }
        return mem;
}

address_t myAlloc(mem_t* mem,int nb)
{
     for(address_t address = 0; address < SIZE; address++) //On parcours le tableau
        {
              for(int caselibre = 0; caselibre <= nb; caselibre++) //On parcours le tableau pour verifie la disponibilte de nb
                {
                    if(mem->vec_log[address+caselibre]!=0)
                    {
                        break;
                    }
                    else if(caselibre==nb)
                    {
                      for(int z=0;z<nb;z++)
                      {
                        mem->vec_log[address+z]=-1;
                      }
                      return address;
                    }
                }

        }
        return -1; // On return -1 en cas de non disponibilte de nb case de libre
}

void myFree(mem_t *mp, address_t p, int sz)
{
for(int freecase=p;freecase < p+sz;freecase++)
{
  mp->mem_log[freecase]=0;
  mp->vec_log[freecase]=0;
}
}

void myWrite(mem_t *mp, address_t p, byte_t val)
{
mp->mem_log[p]=val;

}

byte_t myRead(mem_t *mp, address_t p)
{
return (byte_t)mp->mem_log[p];
}

void display(int tab[SIZE])
{for(int tmp=0;tmp<100;tmp++)
  printf("Indice : %d - Valeur : %d \n",tmp,tab[tmp]);}


int main() {
        mem_t* mem = initMem();
        address_t adr1 = myAlloc(mem, 5);
        address_t adr2 = myAlloc(mem, 10);
        address_t adr3 = myAlloc(mem, 100);
        printf("%d-%d-%d\n",adr1,adr2,adr3);

        myFree(mem, adr2, 10);
        myFree(mem, adr1, 5);
        myWrite(mem, adr3, 543);
        myWrite(mem, adr3+9, 34);

        byte_t val1 = myRead(mem, adr3);
        byte_t val2 = myRead(mem, adr3+9);
        printf("%d-%d\n",val1,val2);

        address_t adr4 = myAlloc(mem, 19);
        display(mem->vec_log);

}
