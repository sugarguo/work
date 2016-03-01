#include <stdio.h>
#include <stdlib.h>
#include "Link.a"

int main()
{
	List = CreateList();
	if (List == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");
	InsertList(List,"test");
	InsertList(List,"test2");
	InsertList(List,"test3");
	ShowList(List);
	DeleteList(List,"test2");
	UpdateList(List,"test3","test5");
	ShowList(List);
}
