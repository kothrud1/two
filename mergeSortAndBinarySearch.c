#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
void bubbleSort(int a, int b, int arr[], int count)
{
	int i, j;
	
	for(i=0; (i+a)<count && (i+a)<b; i++)
	{
		for(j=a+1; j<count && j<=b-i; j++)
		{
			if(arr[j] < arr[j-1]) 
			{
				int temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void mergeSort(int a[], int count)
{
	int size=2, i=0;
	
	while(size<=count)
	{
		i=0;
		while(i<count)
		{
			bubbleSort(i, i+size, a, count);
			i+=size;
		}
		size*=2;
	}
}

int main()
{
	pid_t child_pid;
	int* status = NULL;
	char *str[30];
	int arr[30], n;
	
	printf("Enter number of elements -> ");
	scanf("%d", &n);
	
	int i;
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);
		
	mergeSort(arr,n); 
	printf("\nSorted => ");
	for(i=0; i<n; i++)
		printf("%d, ", arr[i]);
	printf("\n");
	
	
	printf("Forking Now\n");
	child_pid = fork();
	switch(child_pid)
	{
		case -1:
			printf("Error\n");
			break;
		
		case 0:{
			printf("child pid = %d\n", (int)getpid());
			
			asprintf(&str[0], "%d", n);
			int i;
			for(i=1; i<=n; i++)
			{	
				asprintf(&str[i], "%d", arr[i-1]);
			}
				
			execve("./binSearch.out",str,NULL);
			break;
			}
		default:
			wait(status);
			printf("parent pid = %d\n", (int)getppid());
	}
	
}
