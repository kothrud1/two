#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char* argv[])
{
pid_t pid;
int i,a[argc];
for(i=1;i<argc;i++)
{
a[i]=atoi(argv[i]);
}
pid=fork();
if(pid==0)
{
printf("\nChild Process\n");
int i,j,temp;
for(i=1;i<argc;i++)
{
for(j=1;j<argc-i;j++)
{
if(a[j]<a[j+1])
{
temp=a[j];
a[j]=a[j+1];
a[j+1]=temp;
}
}
}
for(i=1;i<argc;i++)
{
printf("\n%d\t",a[i]);
}
}
else
{
wait(NULL);
printf("\nParent Process\n");
int i,j,temp;
for(i=1;i<argc;i++)
{
for(j=1;j<argc-i;j++)
{
if(a[j]>a[j+1])
{
temp=a[j];
a[j]=a[j+1];
a[j+1]=temp;
}
}
}
for(i=1;i<argc;i++)
{
printf("\n%d\t",a[i]);
}
}
printf("\n");
return 0;
}
