#include<stdio.h>
#include<stdlib.h>
void argvToIntArr(char* argv[], int a[], int n)
{
	int i;
	for(i=1; i<=n; i++)
	{
		a[i-1] = atoi(argv[i]);
	}
}

void binarySearch(int a[], int count, int key)
{
	int l=0, h=count-1, m; 
	int found = 0;
	
	while(l <= h)
	{
		m = l + (h-l)/2 ;
		
		if(a[m] == key)
		{
			printf("Found at pos %d :)\n", m);
			found = 1;
			break;
		}
		else if(key > a[m])
			l = m;
		else if(key < a[m])
			h = m;
	}
	
	if(found == 0)
		printf("Not Found :(\n");
}

main(int argc, char* argv[])
{
	int a[30],count=0, i, key;
	printf("Success\n");
	
	count = atoi(argv[0]);
	
	argvToIntArr(argv, a, count);
	
	printf("\nThe array is => ");
	for(i=0; i<count; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	
	printf("Enter the number to search -> ");
	scanf("%d",&key);
	
	binarySearch(a, count, key);
}
