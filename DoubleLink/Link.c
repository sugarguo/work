/******************************************************
* Program Assignment :  通用双向链表
* Author:              Sugarguo
* Date:                2016/03/01 20:00
* Description:          双向链表的动态创建，支持多种数据格式。
*****************************************************/
/*******************************************************
* Source code in :   Link.c  
* Function List:
*  CreateList      初始化双向链表
*  SearchList      查询双向链表中的数据
*  InsertList      将数据插入到双向链表中
*  UpdateList      修改双向链表中的数据
*  DeleteList      删除双向链表中的值
*  ShowList        遍历双向链表中的数据
*******************************************************/


#include <stdio.h>
#include <stdlib.h>


/* 定义双向链表的结构体 */
typedef struct _DoubleLink
{
	void *data; //数据
	struct _DoubleLink *back;  //双向链表的前区
	struct _DoubleLink *next;  //双向链表的后区
}DLNode;

/*******************************************************
* Function Name: 	CreateList
* Purpose: 			创建双向链表
* Params : 
*	@LINEAR		linear	线性表实例
*	@USER_TYPE 	var		类型为USER_TYPE的实例
*	@int (*)() 		cmp		提供接口，让用户定义具体比较函数
* Return: 			int  	返回元素的index值
* Limitation: 	如果返回-1，则代表不存在var的元素
*******************************************************/
DLNode *CreateList()
{
	DLNode *List;
	List = (DLNode *)malloc(sizeof(DLNode));
	if p == NULL:
		printf ("Create MEM ERROR!\n");
	List->back = List;
	List->next = List;
	return List;
}

/*******************************************************
* Function Name: 	SearchList
* Purpose: 			查询双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*	@void 	    *data		无类型数据指针
*******************************************************/
DLNode *SearchList(DLNode *List, void *data)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if p == NULL:
		printf ("Create MEM ERROR!\n");
	else
	{
		p = List;
		p = p->next;
		while(p != List)
		{
			if (p->data == data)
				return p;
			p = p->next;
		}	
	}	
}

/*******************************************************
* Function Name: 	InsertList
* Purpose: 			插入双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*	@void 	    *data		无类型数据指针
*******************************************************/
void InsertList(DLNode *List, void *data)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if p == NULL:
		printf ("Create MEM ERROR!\n");
	else
	{
		p->back = List;
		p->next = List->next;
		List->next->back = p;
		List->next = p;
		p->data = data;
	}
}

/*******************************************************
* Function Name: 	UpdateList
* Purpose: 			更新双向链表
* Params : 
*	@DLNode		*List	        双向链表实例
*	@void 	    *data_search	待查询数据，无类型数据指针
*	@void 	    *data_change	待替换数据，无类型数据指针
*******************************************************/
void UpdateList(DLNode *List, void *data_search, void *data_change)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if p == NULL:
		printf ("Create MEM ERROR!\n");
	else
	{
		p = SearchList(List, data_search);
		p->data = data_change;
	}
}

/*******************************************************
* Function Name: 	DeleteList
* Purpose: 			删除双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*	@void 	    *data		无类型数据指针
*******************************************************/
void DeleteList(DLNode *List, void *data)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if p == NULL:
		printf ("Create MEM ERROR!\n");
	else
	{
		p = SearchList(List, data);
		p->back->next = p->next;
		p->next->back = p->back;
		free(p);
		if( SearchList(List, data)->data != NULL)
			printf("Delete Error!\n");
		else
			printf("Delete OK!\n");	
	}
}

/*******************************************************
* Function Name: 	ShowList
* Purpose: 			遍历双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*******************************************************/
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

void Callbackint(DLNode *List, int *data, void (* ptr)())
{  
    (* ptr)(List,data);  
}

void CallbackString(DLNode *List, int *data, void (* ptr)())
{  
    (* ptr)(List,data);  
}

void CallbackChar(DLNode *List, int *data, void (* ptr)())
{  
    (* ptr)(List,data);  
}


void main()
{
	DLNode *List;
	List = CreateList();
	if (List == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");
	void num = malloc(sizeof(int));
	num = 5;
	printf ("%02x\n",num);
	printf("%d",num);
	Callbackint(List,*num,InsertList);
	ShowList(List);

	InsertList(List,2);
	InsertList(List,3);
	ShowList(List);
	/*DeleteList(List,2);
	UpdateList(List,3,5);
	ShowList(List);
	ShowMessage(List,ShowList);
*/
}
