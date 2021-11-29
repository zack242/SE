#include <stdio.h>
#include <stdlib.h>
#define SIZE 65536
#define SIZE1 32768
typedef short byte_t;
typedef int address_t;
static int pagesize=128;


typedef struct
{
//memoire logique et son vecteur
        int mem_log[SIZE];
        int vec_log[SIZE];

//Page
        int page[256];

//memoire physique et son vecteur
        int physmem[SIZE1];
        int vec_mem[SIZE1];

}mem_t;

mem_t* initMem()
{
        mem_t* mem = malloc(sizeof(mem_t));

        for(int i = 0; i < SIZE; i++)
        {
                //On initialiser la memoire logique et son vecteur a 0
                mem->mem_log[i] = 0;
                mem->vec_log[i] = 0;

                if(i < SIZE1)
                {
                        mem->page[i] = -1; // On initialise la page a -1
                        mem->physmem[i] = 0; // On initialise la page a 0
                }

        }
        return mem;
}

address_t myAllocCont(mem_t* mem,int nb)
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
                                for(int z=0; z<nb; z++)
                                {
                                        mem->vec_log[address+z]=-1;
                                }
                                return address;
                        }
                }

        }

       return EXIT_FAILURE;// On return  FAILLURE en cas de non disponibilte de nb case de libre
}


address_t myAllocRam(int vec_ram[SIZE1],int nb)
{

        for(address_t address = 0; address < SIZE1; address++) //On parcours le tableau
        {
                for(int caselibre = 0; caselibre <= nb; caselibre++) //On parcours le tableau pour verifie la disponibilte de nb
                {
                        if(vec_ram[address+caselibre]!=0)
                        {
                                break;
                        }
                        else if(caselibre==nb)
                        {
                                for(int z=0; z<nb; z++)
                                {
                                        vec_ram[address+z]=-1;
                                }
                                return address;
                        }
                }

        }

      return EXIT_FAILURE;// On return -1 en cas de non disponibilte de nb case de libre
}


void myFreeCont(mem_t *mp, address_t p, int sz)
{
        for(int freecase=p; freecase < p+sz; freecase++)
        {
                mp->mem_log[freecase]=0;
                mp->vec_log[freecase]=0;
        }
}

void myWriteCont(mem_t *mp, address_t p, byte_t val)
{
        mp->mem_log[p]=val;

}

byte_t myReadCont(mem_t *mp, address_t p)
{
        return (byte_t)mp->mem_log[p];
}

void display(int tab[SIZE])
{
        for(int tmp=0; tmp<100; tmp++)
                printf("Indice : %d - Valeur : %d \n",tmp,tab[tmp]);
}


address_t myAlloc(mem_t* mem,int nb)
{
  //la je dois cherche une frame de libre dans la memoire de 128
  //Si pour la page on la trouve pas dans le page alors on lui allouer une nouvelle framme

        address_t address = myAllocCont(mem,nb);
        int page = address/pagesize;

        if(mem->page[page]==-1)
        {
          address_t adress_ram = myAllocRam(&mem->vec_mem[SIZE1],pagesize);
          int frame = adress_ram/pagesize;
          mem->page[page]=frame;
          //printf("Adress ram : %d Frame : %d\n",adress_ram,frame);
        }
          //printf("offset : %d\n",address%pagesize);
        return address;
}



void myFree(mem_t *mp, address_t p, int sz)
{
        for(int freecase=p; freecase < p+sz; freecase++)
        {
                mp->vec_log[freecase]=0;
        }
        address_t address_mem = (mp->page[p/pagesize])*pagesize;
        int offset = p%pagesize;

      //  printf("adress_ram : %d -offset : %d \n",address_mem,offset);

        for(int freecase=address_mem+offset; freecase < p+sz; freecase++)
        {
               mp->vec_mem[freecase]=0;
        }
}


void myWrite(mem_t *mp, address_t p, byte_t val)
{
         address_t address_mem = (mp->page[p/pagesize])*pagesize;
         int offset = p%pagesize;

         mp->physmem[address_mem+offset]=val;
}

byte_t myRead(mem_t *mp, address_t p)
{
        address_t address_mem = (mp->page[p/pagesize])*pagesize;
        int offset = p%pagesize;
        return (byte_t)mp->physmem[address_mem+offset];
}


int main() {

        mem_t* mem = initMem();

        address_t adr1 = myAlloc(mem, 50);
        address_t adr2 = myAlloc(mem, 10);
        address_t adr3 = myAlloc(mem, 100);
        printf("Adresse logique : %d-%d-%d\n",adr1,adr2,adr3);

        myFree(mem, adr1, 50);
        myFree(mem, adr2, 100);

        myWrite(mem, adr3, 543);
        myWrite(mem, adr3+9, 34);

        byte_t val1 = myRead(mem, adr3);
        byte_t val2 = myRead(mem, adr3+9);
        printf("Lecture des valeurs : %d-%d\n",val1,val2);

        address_t adr4 = myAlloc(mem, 19);
      //  display(mem->page);
}
