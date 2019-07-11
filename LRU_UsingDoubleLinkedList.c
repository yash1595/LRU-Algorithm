#include <stdint.h>
#include <stdio.h>

#define MEMSIZE	(4)

typedef struct dd
{
	int val;
	struct dd* next;
	struct dd* prev;
}doublelinkedlist;

doublelinkedlist* head;
doublelinkedlist* tail;
doublelinkedlist* temp;

int AddNode(int);
int Display(void);
int SearchCache(int);
int NumberofNodes(int);
int FreeCache(int);

int main(void)
{
	NumberofNodes(MEMSIZE);

	Display();

	SearchCache(1);
	Display();
	SearchCache(2);
	Display();
	SearchCache(3);
	Display();
	SearchCache(1);
	Display();
	SearchCache(2);
	Display();
	SearchCache(1);
	Display();
	SearchCache(4);
	Display();
	SearchCache(3);
	Display();
	SearchCache(1);
	Display();

	FreeCache(MEMSIZE);
	Display();
    
	return 0;
}

int AddNode(int value)
{
	if(head == NULL)
	{
		head = (doublelinkedlist*)malloc(sizeof(doublelinkedlist));
		if(head == NULL)
		{
			printf("Unable to allocate space for node\n");
			return -2;
		}
		head->val = value;
		tail=head;
		head->prev = NULL;
	}
	else
	{
	    temp=tail;
		tail->next = (doublelinkedlist*)malloc(sizeof(doublelinkedlist));
		if(tail->next == NULL)
		{
			printf("Unable to allocate space for node\n");
			return -2;
		}
		tail->next->val = value;
		tail = tail->next;
		tail->prev = temp;
	}
	tail->next = NULL;

	return 0;
}

int Display(void)
{
	if(head==NULL)
	{
		printf("Add a node first\n");
		return -2;
	}
	else
	{
		temp=head;
		while(temp!=NULL)
		{
			printf("[%d]->",temp->val);
			temp=temp->next;
		}
		printf("NULL\n");
	}
	return 0;
}

int SearchCache(int value)
{
	if(head==NULL)
	{
		printf("Add a node first\n");
		return -1;
	}

	temp = head;														// Store head temporarily.
	while(temp!=NULL)													// Traverse Double Linked List.
	{
		if(temp->val == value)											// If value in list matches given value.
		{
			while(temp!=head)											// Shift all values before the found value to the right.
			{
				temp->val = temp->prev->val;
				temp = temp->prev;
			}
			head->val = value;											// Place the found value at the head.
			return 0;
		}
		temp = temp->next;												// Keep iterating the loop.
	}

	temp = tail->prev;													// For new elements. 
	while(temp!=NULL)													// Shift all value to the right and over-write the last value.
	{
		temp->next->val=temp->val;
		temp = temp->prev;
	}
	head->val = value;													// Place new value at head.
	

	return 0;
}

int NumberofNodes(int number)
{
    static int i=0;
    for(i=0;i<number;i+=1)
    {
        AddNode(0);
    }
    return 0;
}

int FreeCache(int number)
{
	doublelinkedlist** freeing_ptr = &head;
	static int i=0;
	
	for(i=0;i<number;i+=1)
	{
	    free(*freeing_ptr);
	    *freeing_ptr=NULL;
	    freeing_ptr+=1;
	}
	return 0;
}
