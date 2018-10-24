#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#define max 10

typedef struct mat
{
  int a[max][max];
  int m,n,i,j;
}mat;
mat m1,m2,m3,aa;

void display(mat m6)
{
  int i,j;
  printf("Matrix:\n");
  for(i=0;i<m6.m;i++)
  {
    printf("\n");
    for(j=0;j<m6.n;j++)
    {
      printf("\t%d",m6.a[i][j]);
    }
  }
}


mat accept()
{
  mat m5;
  int i,j;
  printf("Enter No of rows and columns:\n");
  scanf("%d%d",&m5.m,&m5.n);

  printf("Enter matrix:\n");
  for(i=0;i<m5.m;i++)
  {
    for(j=0;j<m5.n;j++)
    {
      scanf("%d",&m5.a[i][j]);
    }
  }
  return m5;
}

void *mul(void*m6)
{
int k;
mat *m3 = (mat*)m6;

      m3->a[m3->i][m3->j]=0;
      for(k=0;k<m2.m;k++)
      {
        m3->a[m3->i][m3->j]+=m1.a[m3->i][k] * m2.a[k][m3->j];
      }
}

int main()
{
mat p;
pthread_t tid[5][5];
m1=accept();
m2=accept();
aa.m=m1.m;
aa.n=m2.n;
display(m1);
display(m2);
//mul();

m3.m=m1.m;
m3.n=m2.n;
if(m1.m==m2.n){
for(m3.i=0;m3.i<m1.m;m3.i++)
{
  for(m3.j=0;m3.j<m2.n;m3.j++)
  {

pthread_create(&tid[m3.i][m3.j],NULL,mul,(void*)&m3);
pthread_join(tid[m3.i][m3.j],NULL);
}
}
printf("\nMultiplication\t");
display(m3);
}
else{
  printf("Multiplication is not possible\n");
}



  return 0;
}
