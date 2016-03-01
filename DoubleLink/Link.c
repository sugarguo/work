#include <stdio.h>
#include <stdlib.h>

typedef struct _DoubleLink
{
	void *data;
	struct _DoubleLink *back;
	struct _DoubleLink *next;
}DLNode;

DLNode *CreateList()
{
	DLNode *List;
	List = (DLNode *)malloc(sizeof(DLNode));
	List->back = List;
	List->next = List;
	return List;
}

DLNode *SearchList(DLNode *List, void *data)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	p = List;
	p = p->next;
	while(p != List)
	{
		if (p->data == data)
			return p;
		p = p->next;
	}
}


void InsertList(DLNode *List, void *data)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	p->back = List;
	p->next = List->next;
	List->next->back = p;
	List->next = p;
	p->data = data;
}

void UpdateList(DLNode *List, void *data_search, void *data_change)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	p = SearchList(List, data_search);
	p->data = data_change;
}


void DeleteList(DLNode *List, void *data)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	p = SearchList(List, data);
	p->back->next = p->next;
	p->next->back = p->back;
	free(p);
	if( SearchList(List, data)->data != NULL)
		printf("Delete Error!\n");
	else
		printf("Delete OK!\n");
	
}


void ShowList(DLNode *List)
{
	DLNode *p;
	p = List;
	p = p->next;
	while(p != List)
	{
		printf ("%s\n", p->data);
		p = p->next;
	}
}

void ShowMessage(DLNode *List, void (* ptr)())
{  
    (* ptr)(List);  
}


int main()
{
	DLNode *List;
	List = CreateList();
	if (List == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");
	InsertList(List,"test1");
	InsertList(List,"test2");
	InsertList(List,"test3");
	ShowList(List);
	DeleteList(List,"test2");
	UpdateList(List,"test3","test5");
	ShowList(List);
	ShowMessage(List,ShowList);
}
