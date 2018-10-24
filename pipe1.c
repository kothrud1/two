#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
int ret1,fd1[2],ret2,fd2[2];
pid_t pd;
char filename[10],buff1[20],buff2;
char ch,data[6];
FILE *fp;
int i=0;

//char filedata[6];
//printf("ENter data\n");
//scanf("%s\n",filedata);

ret1 = pipe(fd1);
if(ret1<0)
{
  printf("Pipe Error\n");
  exit(1);
}

ret2 = pipe(fd2);
if(ret2<0)
{
  printf("Pipe Error\n");
  exit(1);
}
pd = fork();
if(pd==0)
{
  /*Child Process getting name from Parent*/
  close(fd1[1]);
  read(fd1[0],(char*)buff1,100);
  close(fd1[0]);
  printf("filename:%s\n",buff1);
//read frome file and sending to parent
close(fd2[0]);
fp=fopen(buff1,"r");
//fprintf(fp,"%s\n",data);
while(!feof(fp))
{
  ch=fgetc(fp);
  write(fd2[1],&ch,1);
}
fclose(fp);
close(fd2[1]);

}

else
{
    /*Parent Process sending name to child */
  printf("Enter name of file:\n");
  scanf("%s",filename);
  close(fd1[0]);
  write(fd1[1],(char*)filename,sizeof(filename));
  close(fd1[1]);


  close(fd2[1]);
  while(read(fd2[0],(char*)&buff2,1)>0)
  printf("%c",buff2);
  close(fd1[0]);

}

return 0;
}
