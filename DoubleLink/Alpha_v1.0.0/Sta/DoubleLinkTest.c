/**
* @file			DoubleLinkTest.c  
* @brief		通用双向链表测试程序 \n
* 使用DoubleLink.h这个sugarguo编写的通用双向链表的头文件接口，进行双向链表的操作测试。
* @author		Sugarguo
* @email    	sugarguo@live.com
* @date			2016/03/01 20:00
* @version		v1.0.0 
* @copyright	EmbedWay 恒为科技武汉研发中心 By:Sugarguo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h> //win请用这个头文件
#include <unistd.h>
#include "DoubleLink.h"

#define MAX_LINE 1024


struct Wordnum{
	char *word;
	int num;	
	int length;
};

/*去除字符串右边空格*/  
void VS_StrRTrim(char *pStr)  
{  
    char *pTmp = pStr+strlen(pStr)-1;  
      
    while (*pTmp == ' ')   
    {  
        *pTmp = '\0';  
        pTmp--;  
    }  
}  
  
/*去除字符串左边空格*/  
void VS_StrLTrim(char *pStr)  
{  
    char *pTmp = pStr;  
      
    while (*pTmp == ' ')   
    {  
        pTmp++;  
    }  
    while(*pTmp != '\0')  
    {  
        *pStr = *pTmp;  
        pStr++;  
        pTmp++;  
    }
    *pStr = '\0';
    *pStr = '\0';  
}


DLNode *StatisticsContent(DLNode *List_Content)
{
	DLNode *p;
	int i = 1;

	p = List_Content->next;
	while(p->next != List_Content)
	{
		if( strcasecmp((char *)p->data , (char *)p->next->data) == 0)
			i++;
		else
		{
			printf("Word :\t%s\t\t ; Show :\t%d \n",(char *)p->data,i);
			i = 1;
		}
		p = p->next;
	}
	return List_Content;
}

DLNode *GetFileContent(DLNode *List_Content, char *filename)
{
	FILE *novelfile,*fp;
	fp=fopen("temp.txt","w");
	fclose(fp);
	int i = 0, word = 0;
	char str[100];

	if((novelfile = fopen(filename,"r")) == NULL)
	{
		printf("ERROR! File can't be Opened!\n");
		exit(1);
	}
	while(( word = fgetc(novelfile)) != EOF)	//判断文件是否结束
	{
		if((word >= 'A' && word <= 'Z') || (word >= 'a' && word <= 'z'))
		{
			str[i] = (char)word;
			i++;
		}
		else
		{
			if(strlen(str) == 0 )
				continue;
			//printf("%s\n",*wordstr);
			char *wordstr;
			wordstr = (char *)malloc(sizeof(char));
			if( wordstr == NULL )
				printf ("Create MEM ERROR!\n");
			else
			{
				VS_StrLTrim(str);
				VS_StrRTrim(str);
				strcpy(wordstr,str);
				InsertList(List_Content,(void *)wordstr);
				i = 0;
				memset(str,'\0',sizeof(str));
				wordstr=NULL;
				free(wordstr);
			}
		}
	}
	//ShowList(List_Content,2);
	return List_Content;
}

/**
* @brief main \n
* 测试程序的主函数，进行int以及char的创建、增、删、改、查、排序、清空操作。
* @param[in]	argc		带int参数形式
* @param[in]	*argv[]		带char参数形式
* @return		函数默认返回值
*/
int main( int argc, char *argv[] )
{
	//char *filename = "LittleTest.txt";
	char *filename = "Harry Potter and the Order of the Phoenix.txt";
	//FILE *linefile;
	
	DLNode *List_Content;
	DLNode *List_Num;

	List_Content = CreateList();
	List_Num = CreateList();
	if (List_Content == NULL || List_Num == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");

	List_Content = GetFileContent(List_Content,filename);
	ShowList(List_Content,2);
	SequenceList(List_Content,2,CallBackSequence);
	ShowList(List_Content,2);
	StatisticsContent(List_Content);

	DropList(List_Content);

	
	return 0;
}
