/******************************************************************************  
#Implementation of LRU Algorithm  
@Auhtor :	Yash Gupte  
@Dated	:	01/03/2018  
*******************************************************************************/  

#include <stdio.h>
#define SIZE 	3

int LRUArray[3]={0};
int LRU_index = 0;
int* rear  = &LRUArray[2];
int index=0;

typedef enum{miss=0,hit=1}cache;
cache SearchEntry(int);
void ShiftLRU();
void UpdateLRU(int);
void PageEntry(int);
void Display(void);

int main(void)
{	
	int element=0;
	while(1)
	{
		printf("Enter the element to search\n");
		scanf("%d",&element);
		PageEntry(element);
		Display();
	}
	
	return 0;
}

void PageEntry(int element)
{	
	cache status=0;
	if(status=SearchEntry(element))
	{
		ShiftLRU();
		return;
	}
	UpdateLRU(element);
}

void ShiftLRU()
{
	static int temp=0,i=0;
	temp=LRUArray[index];
	for(i=index-1;i>=0;i--)
	{
		LRUArray[i+1]=LRUArray[i];
	}
	LRUArray[0]=temp;
	if(LRU_index!=SIZE-1){LRU_index=(LRU_index+1)%(SIZE);}
	printf("LRU_index:%d\n",LRU_index);
}

cache SearchEntry(int element)
{	
	static int i=0;
	for(i=0;i<3;i++)
	{
		if(LRUArray[i]==element)
		{
			index=i;
			return hit;
		}
	}
	return miss;
}

void UpdateLRU(int element)
{	
	static int i=0;
	for(i=0;i<SIZE;i++)
	{
		if(LRUArray[i]==0)
			{
				LRUArray[i]=element;
				return;
			}

	}
	for(i=LRU_index-1;i>=0;i--)
	{
		LRUArray[(i+1)]=LRUArray[i];
	}
	LRUArray[0]=element;
	if(LRU_index==0){LRU_index=(LRU_index+2);printf("LRU_index:%d\n",LRU_index);return;}
	if(LRU_index!=SIZE-1)LRU_index=(LRU_index+1);
	printf("LRU_index:%d\n",LRU_index);
}

void Display()
{
	static int i=0;
	for(i=0;i<SIZE;i++)
	{
		printf("|%d",LRUArray[i]);
	}
	printf("|\n");
}
