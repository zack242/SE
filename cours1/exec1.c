#include <stdio.h>
#include <unistd.h>

int main()
{
  int i = 4 ;
  printf("%d\n",getpid());
  i++;
  printf("%d\n",i);
  fork();
  char *args[]={"/Users/zack/dev/SE/cours1/execHello",NULL};
  execv(args[0],args);

}
