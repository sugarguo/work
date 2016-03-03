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
#include <string.h>

#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}


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
	if( List == NULL)
		printf ("Create MEM ERROR!\n");
	List->back = List;
	List->next = List;
	return List;
}

/*******************************************************
* Function Name: 	CallBackSearch
* Purpose: 			回调函数，比较内容是否相同
* Params : 
*	@void		one		比较的第一个内容
*	@void 		two		比较的第二个内容
*	@int 		judge	提供接口，让用户定义具体比较函数
* Return: 		int  	返回元素的index值
* Limitation: 	如果返回1，则代表不相同
*******************************************************/
int CallBackSearch(void *one, void *two, int judge)
{
	//printf("%d    callback\n",judge);
	//printf("%s  %s\n",(char *)one,(char *)two);
	if(judge == 0)
	{
		if(*(int *)one == *(int *)two && one == two )
		{
			return 0;
		}
		else
			return 1;	
	}
	else if(judge == 1)
	{
		if(*(char *)one == *(char *)two )
			return 0;
		else
			return 1;	
	}
	else if(judge == 2)
	{
		if(strcmp((char *)one , (char *)two) == 0 )
			return 0;
		else
			return 1;	
	}
	else
	{
		printf("请使用0:int 1:float 2:char ，目前仅支持这三种！\n");	
	}
}

/*******************************************************
* Function Name: 	CallBackShow
* Purpose: 			回调函数，显示内容
* Params : 
*	@void		one		需要显示的内容
*	@int 		judge		提供接口，让用户定义具体比较函数
* Return: 		int  	返回元素的index值
* Limitation: 	如果返回1，则代表不相同
*******************************************************/
int CallBackShow(void *one, int judge)
{
	if(judge == 0)
	{
		printf("%d\n", *(int *)one);
	}
	else if(judge == 1)
	{
		printf("%c\n", *(char *)one);
	}
	else if(judge == 2)
	{
		printf("%s\n", (char *)one);
	}
	else
	{
		printf("请使用0:int 1:float 2:char ，目前仅支持这三种！\n");	
	}
}


/*******************************************************
* Function Name: 	CallBackSequence
* Purpose: 			回调函数，显示内容
* Params : 
*	@void		one		需要显示的内容
*	@int 		judge		提供接口，让用户定义具体比较函数
* Return: 		int  	返回元素的index值
* Limitation: 	如果返回1，则代表不相同
*******************************************************/
int CallBackSequence(DLNode *List, DLNode *p_one, DLNode *p_two, int judge)
{
	DLNode *temp=NULL;
	void *temp_data;
	if(judge == 0)
	{
		for(p_one = p_one; p_one->next != List; p_one = p_one->next)
		{
			temp=p_one;
			for(p_two = p_one->next; p_two != List; p_two = p_two->next)
			{
				if(*(int *)p_two->data > *(int *)temp->data )
				{
					temp = p_two;
				}
			}
			if (temp != p_one)
			{
				temp_data=p_one->data;
				p_one->data=temp->data;
				temp->data=temp_data;
			}
		}
		return 0;
	}
	else if(judge == 1)
	{
		for(p_one = p_one; p_one->next != List; p_one = p_one->next)
		{
			temp=p_one;
			for(p_two = p_one->next; p_two != List; p_two = p_two->next)
			{
				if(strcmp((char *)p_two->data , (char *)temp->data) < 0 )
				{
					temp = p_two;
				}
			}
			if (temp != p_one)
			{
				temp_data=p_one->data;
				p_one->data=temp->data;
				temp->data=temp_data;
			}
		}
		return 0;
	}
	else if(judge == 2)
	{
		for(p_one = p_one; p_one->next != List; p_one = p_one->next)
		{
			temp=p_one;
			for(p_two = p_one->next; p_two != List; p_two = p_two->next)
			{
				if(strcmp((char *)p_two->data , (char *)temp->data) > 0 )
				{
					temp = p_two;
				}
			}
			if (temp != p_one)
			{
				temp_data=p_one->data;
				p_one->data=temp->data;
				temp->data=temp_data;
			}
		}
		return 0;
	}
	else
	{
		printf("请使用0:int 1:float 2:char ，目前仅支持这三种！\n");	
	}
}

/*******************************************************
* Function Name: 	SearchList
* Purpose: 			查询双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*	@void 	    *data		无类型数据指针
*	@int 	    judge		int类型选择类型数
*	@int 	    CallBack	回调函数判断是否相同
*******************************************************/
DLNode *SequenceList(DLNode *List, int judge, int (*CallBackSequence)(DLNode *,DLNode *, DLNode *, int judge))
{
	DLNode *p_one;
	DLNode *p_two;
	p_one = List->next;
	//p_one = p_one->next;
	p_two = List->next;
	//p_two = p_two->next;
	CallBackSequence( List, p_one, p_two, judge );
	printf("Done\n");
}

/*******************************************************
* Function Name: 	SearchList
* Purpose: 			查询双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*	@void 	    *data		无类型数据指针
*	@int 	    judge		int类型选择类型数
*	@int 	    CallBack	回调函数判断是否相同
*******************************************************/
DLNode *SearchList(DLNode *List, void *data, int judge, int (*CallBackSearch)(void *, void *, int judge))
{
	DLNode *p;
	p = List;
	p = p->next;
	while(p != List)
	{
		//CallBackShow(p->data, judge);
		if ( CallBackSearch( p->data, data, judge ) == 0 )
		{
			return p;
		}
		p = p->next;
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
	if( p == NULL )
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
void UpdateList(DLNode *List, void *data_search, void *data_change, int judge)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if( p == NULL )
		printf ("Create MEM ERROR!\n");
	else
	{
		p = SearchList(List, data_search, judge, CallBackSearch);
		p->data = data_change;
		printf("Update OK!\n");
	}
}

/*******************************************************
* Function Name: 	DeleteList
* Purpose: 			删除双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*	@void 	    *data		无类型数据指针
*******************************************************/
void DeleteList(DLNode *List, void *data, int judge)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if( p == NULL )
		printf ("Create MEM ERROR!\n");
	else
	{
		p = SearchList(List, data, judge, CallBackSearch);
		p->back->next = p->next;
		p->next->back = p->back;
		free(p);
		if( SearchList(List, data, judge, CallBackSearch) == 0)
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
void ShowList(DLNode *List, int judge)
{
	printf("Start Show List!\n");
	DLNode *p;
	p = List;
	p = p->next;
	while(p != List)
	{
		//printf ("%s\n", p->data);
		CallBackShow(p->data, judge);
		//printf ("%p\n", *p->data);
		p = p->next;
	}
}

/*******************************************************
* Function Name: 	DropList
* Purpose: 			删除双向链表
* Params : 
*	@DLNode		*List	    双向链表实例
*******************************************************/
void DropList(DLNode *List)
{
	DLNode *p;
	p = (DLNode *)malloc(sizeof(DLNode));
	if( p == NULL )
		printf ("Create MEM ERROR!\n");
	else
	{
		p = List;
		p = p->next;
		while(p != List)
		{
			p->back->next = p->next;
			p->next->back = p->back;
			free(p);
			p = p->next;
		}
	}
}

void main()
{
	DLNode *List;
	int judge = 0;
	int num[1000],i = 0;
	for(i = 0; i < 1000; i++)
		num[i] = rand();
	List = CreateList();
	if (List == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");
	for(i = 0; i < 1000; i++)
		InsertList(List,(void *)&num[i]);//(num + i));
	ShowList(List,judge);
	SequenceList(List,judge,CallBackSequence);
	ShowList(List,judge);
	SearchList(List,&num[1],judge,CallBackSearch);
	UpdateList(List,&num[1],&num[5],judge);
	ShowList(List,judge);
	DeleteList(List,&num[5],judge);
	ShowList(List,judge);
	DropList(List);
	ShowList(List,judge);



	char *test1 = "test1";
	char *test2 = "test2";
	char *test3 = "test3";
	char *test5 = "test5";
	List = CreateList();
	if (List == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");
	InsertList(List,test1);
	InsertList(List,test2);
	InsertList(List,test3);
	ShowList(List,2);
	SequenceList(List,2,CallBackSequence);
	SearchList(List,test2,2,CallBackSearch);
	UpdateList(List,test1,test5,2);
	ShowList(List,2);
	DeleteList(List,test5,2);
	ShowList(List,2);
	DropList(List);
	ShowList(List,2);


	test1 = "a";
	test2 = "b";
	test3 = "c";
	test5 = "d";
	List = CreateList();
	if (List == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");
	InsertList(List,test1);
	InsertList(List,test2);
	InsertList(List,test3);
	ShowList(List,1);
	SequenceList(List,1,CallBackSequence);
	ShowList(List,1);
	SearchList(List,test2,1,CallBackSearch);
	UpdateList(List,test1,test5,1);
	ShowList(List,1);
	DeleteList(List,test5,1);
	ShowList(List,1);
	DropList(List);
	ShowList(List,1);
}
