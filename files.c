#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int create_file(char*);
void view(char*);
int search(char*,int);
int insert(char*,int,char*);
int delete(char*,int);
int exist(char*);
void delete_file(char*);

typedef struct
{
int roll;
char name[20];
}rec;

int main()
{
int rollno,ch,ret_in,found=0;
char* filename=(char*)malloc(sizeof(char));
char* name=(char*)malloc(sizeof(char));
printf("Enter the name of File\n");
scanf("%s",filename);
while(1)
{
printf("\n1.Create File\n2.View File\n3.Insert Records\n4.Delete Records\n5.Search Records\n6.Delete File\n7.Exit\nEnter your choice\n");
scanf("%d",&ch);
switch(ch)
{
case 1: create_file(filename);
	break;
case 2: view(filename);
	break;
case 3: printf("Enter Roll No\n");
	scanf("%d",&rollno);
	found=search(filename,rollno);
	if(found==1)
	{
	printf("Record with this Roll No exists\n");
	}
	else
	{
	printf("Enter Name");
	scanf("%s",name);
	ret_in=insert(filename,rollno,name);
	if(ret_in < 0)
	{
	printf("Record Not Inseeted");
	}
	else
 	{
	printf("Record Inserted Succesfully\n");
	}
	}
	break;
case 4: printf("Enter Roll No to be deleted\n");
	scanf("%d",&rollno);
	ret_in=delete(filename,rollno);
	break;
case 5: printf("Enter Roll No\n");
	scanf("%d",&rollno);
	found=search(filename,rollno);
	if(found==0)
	{
	printf("Record Not Present\n");
	}
	else
	{
	printf("Record found in File\n");
	}
	break;
case 6: delete_file(filename);
	break;
case 7: exit(0);
}
}
}
int create_file(char* filename)
{
int fd;
fd=creat(filename,0666);
if(fd==-1)
{
printf("File Creation Error\n");
}
else
{
printf("File created Successfully\n");
return fd;
}

}
int insert(char* filename,int roll,char* name)
{
rec buf;
int fd,ret_in;
fd=open(filename,O_WRONLY|O_APPEND,S_IRUSR|S_IWUSR);
if(fd<0)
{
printf("File Opening Error\n");
}
buf.roll=roll;
strcpy(buf.name,name);
ret_in=write(fd,&buf,sizeof(rec));
close(fd);
return ret_in;
}
int search(char*filename,int roll)
{
rec buf;
int rec_found=0;
int ret_in,fd,temproll;
char* tname=(char*)malloc(sizeof(char));
fd=open(filename,O_RDONLY);
if(fd<0)
{
printf("File buffer Error");
}
while((ret_in=read(fd,&buf,sizeof(buf)))>0)
{
temproll=buf.roll;
strcpy(tname,buf.name);
if(roll==temproll)
{
rec_found=1;
printf("%d\t%s\n",temproll,tname);
}
}
return rec_found;
}
int exists(char* filename)
{
int ret_exists;
ret_exists=access(filename,F_OK);
return ret_exists;
}
void delete_file(char* filename)
{
int ret_file,ret_exists;
ret_exists=exists(filename);
if(ret_exists==0)
{
printf("File Deleted");
ret_file=remove(filename);
}
else
{
printf("File Not Present");
}
}

void view(char filename[10])
{
rec buf;
int fd,troll,ret_in;
char tname[20];
fd=open(filename,O_RDONLY);
printf("\nRoll No\tName\n");
while((ret_in=read(fd,&buf,sizeof(rec)))>0)
{
troll=buf.roll;
strcpy(tname,buf.name);
printf("%d\t%s\n",troll,tname);
}
close(fd);
}
int delete(char* filename,int roll)
{
rec buf;
int ret_in,fd1,fd2,found=0,temproll,temp=1;
char* tfile=(char*)malloc(sizeof(char*));
char* tname=(char*)malloc(sizeof(char*));
off_t ret;
if((fd1=open(filename,O_RDONLY))<0)
{
printf("Error in opening");
}
fd2=open("temp.dat",O_CREAT|O_WRONLY,S_IRWXU);
if(fd2==-1)
{
printf("Error");
exit(0);
}
while((ret_in=read(fd1,&buf,sizeof(rec)))>0)
{
temproll=buf.roll;
strcpy(tname,buf.name);
if(temproll==roll)
{
printf("Deletion of Record Successfull");
}
else
{
write(fd2,&buf,sizeof(rec));
}
}
close(fd1);
close(fd2);
remove(filename);
rename("temp.dat",filename);
return found;

}
