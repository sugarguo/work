#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "DoubleLink.h"


/**
 * @brief 定义双向链表的结构体
 * @param[in]	*data	双向链表中的数据
 * @param[in]	*back	返回指针
 * @param[in]	*next	前进指针
 */
typedef struct _NetPacket
{
	int np_id;
	int np_df;
	int np_mf;
	int np_off;
	u_char *np_packet;
}NetPacket;



/**
 * @brief 定义双向链表的结构体
 * @param[in]	*data	双向链表中的数据
 * @param[in]	*back	返回指针
 * @param[in]	*next	前进指针
 */
typedef struct _NetFlag
{
	int tol_len;
	int last_fregment;
	int first_fregment;
	int cap_len;
	int np_id;
	DLNode *Two_List;
}NetFlag;




int CallBackCmpOff(const void *one, const void *two)
{
	return(((NetPacket *)two)->np_off - ((NetPacket *)one)->np_off);
}

int CallBackCmpSOff(const void *one, const void *two)
{
	if( ( (((NetPacket *)one)->np_off) - (((NetPacket *)two)->np_off) ) < 0)
		return 1;
	else
		return 0;
}

int CallBackCmpSId(const void *one, const void *two)
{
	return ( ((NetFlag *)one)->np_id - ((NetFlag *)two)->np_id);
}


int CallBackCmpId(const void *one, const void *two)
{
	return(((NetPacket *)one)->np_id - ((NetPacket *)two)->np_id);
}


void CallBackShowNetPacketOff(const void *data)
{
	DLNode *p,*Two_List;
	NetPacket *netpacket = NULL;
	Two_List = ((NetFlag *)data)->Two_List;

	p = ((DLNode *)Two_List)->next;
	printf("np_id : %d \n",((NetFlag *)data)->np_id);

	while(p != ((DLNode *)Two_List))
	{
		netpacket = p->data;
		printf("show_np_id && off : %d  %d\n",netpacket->np_id, netpacket->np_off);
		p = p->next;
	}
}



/**
 * @brief CallBackDropNetPacket \n
 * 回调函数，删除List
 * @param[in]	*List		需要删除的内容
 */
void CallBackDropNetPacket(DLNode * temp)
{
	free( ((NetPacket *) (temp->data))->np_packet );
	free(temp->data);
	((NetPacket *)(temp->data))->np_packet = NULL;
	temp->data = NULL;
}



/**
* @brief CallBackDeleteNode \n
* 回调函数，删除Node
* @param[in]	*p		需要删除的内容
*/
void CallBackDeleteNetPacket(DLNode *p)
{
	printf("do");
	p->back->next = p->next;
	p->next->back = p->back;
	free(p->data);
	p->data = NULL;
	DLNode *temp = NULL;
	temp = p;
	p = p->next;
	DropList(((NetFlag *)(temp->data))->Two_List, CallBackDropNetPacket);
	free(temp);
}


DLNode *Judge(DLNode *Two_List,void *data, int (*CallBackCmp)(const void *, const void *))
{

	DLNode *p;
	NetPacket *netpacket = NULL;

	p = Two_List->back;

	while(p != Two_List)
	{
		if(CallBackCmp(p->data,data) > 0)
		{
			InsertList(p, data);
			return p;
		}
		else
		{
			;
		}
		p = p->back;
	}
	InsertList(p, data);
}



void insnet(DLNode *Two_List, int np_id)
{
	int i = 0;
	NetPacket *netpacket = NULL;
	DLNode *p = NULL;

	for(i = 0; i <= 20; i++)  
	{
		netpacket = (NetPacket*)malloc(sizeof(NetPacket));
		netpacket->np_id = np_id;
		netpacket->np_df = i;
		netpacket->np_mf = i;
		netpacket->np_off = rand() % 100;

		p = SearchList(Two_List, (void *)netpacket, CallBackCmpSOff);
/*
		if( p == NULL)
		{
			InsertList(Two_List->next ,(void *)netpacket);
		}
		else
		{
			InsertList(p->back ,(void *)netpacket);
		}
*/
		Judge(Two_List,(void *)netpacket, CallBackCmpOff);
	}

}


void insid(DLNode *List,int i)
{
	DLNode *Two_List = NULL;
	Two_List = CreateList();
	NetFlag *netflag = NULL;
	netflag = (NetFlag*)malloc(sizeof(NetFlag));

	netflag->np_id = i;
	netflag->Two_List = Two_List;

	InsertList(List, netflag);

	insnet(netflag->Two_List,i);

}




int main(int argc, char **argv)
{
	DLNode *List = NULL;
	List = CreateList();
	int i = 0;
	for(i = 0; i <= 5; i++)  
	{
		insid(List, i);
	}

	ShowList(List, 2, CallBackShowNetPacketOff);

	//DLNode *p = NULL;
	//p = SearchList(List, 2, CallBackCmpSId)
	NetFlag *netflag = NULL;
	netflag = (NetFlag*)malloc(sizeof(NetFlag));

	netflag->np_id = 2;


	DeleteList(List, netflag, CallBackCmpSId, CallBackDeleteNode);

	//DropList(Two_List, CallBackDropNetPacket);
	ShowList(List, 2, CallBackShowNetPacketOff);


	return 0;
}


