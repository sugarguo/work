/**
* @file			NetPacket.c  
* @brief		网络包分析头 \n
* 网络包分析头。
* @author		Sugarguo
* @email    	sugarguo@live.com
* @date			2016/03/22 10:00
* @version		v1.0.0 
* @copyright	EmbedWay 恒为科技武汉研发中心 By:Sugarguo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
	struct _NetPacket *next;  ///<双向链表的后区
}NetPacket;


/**
 * @brief InsertNetPacket \n
 * 插入数据包结构体，根据off大小排列
 * @date   2016-03-11
 * @author Sugarguo
 * @param  : 参数说明如下表：
 * name      | type      |description of param 
 * ----------|-----------|--------------------
 * *List     | DLNode    |双向链表默认链表接口
 * *data     | void      |需要插入的数据指针
 * @return    返回值说明如下：
 * name      | type      | description of value
 * ----------|-----------|----------------------
 * null      | null      | null
 * @warning   null
 * @attention null
 * @note      插入双向链表，根据双向链表的接口插入数据
 * @todo      null
 */
void InsertNetPacket(NetPacket *netnode, NetPacket *netdata)
{
	//printf("%d  \n",netnode->np_off );
	printf("%d  \n",netdata->np_off );
	NetPacket *netinsdata = (NetPacket *)malloc(sizeof(NetPacket));
	netinsdata = netdata;
	printf("Enter1\n");
	do
	{
	printf("Enter2\n");
	printf("%d  \n",netnode->np_off );
	printf("%d  \n", netinsdata->np_off);
		if(netnode->np_off < netinsdata->np_off)
		{
			netnode->next;
			if(netnode->next == NULL)
			{
printf("NULL\n");
				netnode->next = NULL;
				netnode = netinsdata;
				printf("Enter4\n");
				break;				
			}
	printf("Enter3\n");
		}
		else
		{
			//netinsdata->next = netinsdata;
			netnode->next = NULL;
			netnode = netinsdata;
	printf("Enter4\n");
			break;
		}
	}while(netnode->next != NULL);
}


/**
 * @brief DeleteNetPacket \n
 * 输入结构体节点，删除主链表下的全部数据
 * @date   2016-03-21
 * @author Sugarguo
 * @param  : 参数说明如下表：
 * name      | type      |description of param 
 * ----------|-----------|--------------------
 * *netdata  | NetPacket |网络数据包结构体默认接口
 * @return    返回值说明如下：
 * name      | type      | description of value
 * ----------|-----------|----------------------
 * null      | null      | null
 * @warning   null
 * @attention null
 * @note      输入结构体节点，删除主链表下的全部数据
 * @todo      null
 */
void DeleteNetPacket(NetPacket *netdata)
{
	NetPacket *temp = NULL;
	temp = netdata;
	do
	{
		NetPacket *temp_np = NULL;
		temp_np = temp;
		free(temp_np->np_packet);
		temp_np->np_packet = NULL;
		temp = temp->next;
		free(temp_np);
	}while(temp->next != NULL);
	//free(temp->np_packet);
	//temp->np_packet = NULL;
	free(temp);
}


