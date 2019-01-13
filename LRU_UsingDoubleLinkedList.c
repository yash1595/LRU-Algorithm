#include <stdio.h>
#define MEMSIZE 3

struct doublelinked{
	int data;
	struct doublelinked* next;
	struct doublelinked* prev;
};

typedef struct doublelinked node;
node* head=NULL;
node* tail=NULL;

int count=0;

node* node1;
node* node2;
node* node3;

void InitCache(void);
void CacheSearch(void);
void DiplayCache(void);

void InitCache()
{
	node1 = (node*)malloc(sizeof(node));
	node2 = (node*)malloc(sizeof(node));
	node3 = (node*)malloc(sizeof(node));

	if(node1 && node2 && node3 != NULL)
	{
		node3->data=node2->data=node1->data=0;
		
		node1->prev=NULL;
		node1->next=node2;

		node2->prev=node1;
		node2->next=node3;

		node3->prev=node2;
		node3->next=NULL;
			
	}

	head=node1;
	tail=node3;
}

void CacheSearch(int data)
{
	node* temp=head;
	int count=0;
	int found=0;
	int i=0;
	while(temp!=NULL)
	{
		if(temp->data==data){found=1;break;}
		++count;
		temp=temp->next;
	}
	if(found==1)
	{
		int temporary_data=temp->data;				// Shifts the data from left to right.
		while(count!=0)								// Eg.[3,2,1]=>where 1 is LRU(Least Recently Used) and 3 is RU(Recently Used). User requests for 1;
		{										    // One is placed at in index '0' and the previous numbers are shifted to right by 1 index.
			temp->data=temp->prev->data;			// The new array will be:[1,3,2]. Now index'0' has 1 which is RU and index'2' has 
			temp=temp->prev;						// 2 which is the LRU.
			--count;
		}
		head->data=temporary_data;
		found=0;
	}
	else
	{
		for(i=0;i<MEMSIZE-1;++i)					// Adds new element at index'0'.
		{											// Eg.[3,2,1]=>where 1 is LRU(Least Recently Used) and 3 is RU(Recently Used). User requests for 4;
			tail->data=tail->prev->data;			// Four is absent from the array. This results in, 1 being removed from the array and elements being 
			tail=tail->prev;						// shifted to right by 1. The index'0' is now replaced with value 4. The new array will be:[4,3,2].
		}
		head->data=data;
	}
	head=node1;
	tail=node3;
}

void DiplayCache()
{
	node*temp = head;
	while(temp!=NULL)
	{
		printf("[%d]=>",temp->data);
		temp=temp->next;
	}
	printf("NULL\n");
}

int main(void)
{
	InitCache();
	CacheSearch(1);
	DiplayCache();
	CacheSearch(2);
	DiplayCache();
	CacheSearch(3);
	DiplayCache();
	CacheSearch(4);
	DiplayCache();
	CacheSearch(2);
	DiplayCache();
	CacheSearch(8);
	DiplayCache();
	CacheSearch(6);
	DiplayCache();
	return 0;
}

