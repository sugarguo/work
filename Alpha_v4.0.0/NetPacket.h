/**
* @file			NetPacket.h  
* @brief		网络包分析头 \n
* 网络包分析头。
* @author		Sugarguo
* @email    	sugarguo@live.com
* @date			2016/03/22 10:00
* @version		v1.0.0 
* @copyright	EmbedWay 恒为科技武汉研发中心 By:Sugarguo
*/


#ifndef __NETPACKET_H__
#define __NETPACKET_H__


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
void InsertNetPacket(NetPacket *netnode, NetPacket *netdata);


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
void DeleteNetPacket(NetPacket *netdata);


int ShowNetPacket(NetPacket *netdata, int judge, void (*CallBackShow)(const void *));

#endif
