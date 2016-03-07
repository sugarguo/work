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


void WriteFile(char writestr[100])
{
	FILE *fp;
	fp=fopen("temp.txt","a+");
	fseek(fp, 0, SEEK_END);
	fprintf(fp,"%s\n", writestr);
	fclose(fp);
}

void WriteFileContent(char *filename)
{
	FILE *novelfile,*fp;
	fp=fopen("temp.txt","w");
	fclose(fp);
	int i = 0,j = 0,word;
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
			WriteFile(str);
			i = 0;
			
			memset(str,'\0',sizeof(str));
		}
	}
}


DLNode *GetFileContent(DLNode *List_Content, char *filename)
{
	FILE *novelfile,*fp;
	fp=fopen("temp.txt","w");
	fclose(fp);
	int i = 0,j = 0,word;
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
			strcpy(wordstr,str);
			//wordstr = str;
			InsertList(List_Content,(void *)wordstr);
			WriteFile(str);
			i = 0;
			
			memset(str,'\0',sizeof(str));
		}
	}
	ShowList(List_Content,2);
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
	char *filename = "LittleTest.txt";
	FILE *linefile;
	
	DLNode *List_Content;
	DLNode *List_Num;

	List_Content = CreateList();
	List_Num = CreateList();
	if (List_Content == NULL || List_Num == NULL)
		printf("Error!\n");
	else
		printf("OK!Create OK!\n");


	WriteFileContent(filename);
	GetFileContent(List_Content,filename);


	if((linefile = fopen("temp.txt","r")) == NULL)
	{
		printf("ERROR! File can't be Opened!\n");
		exit(1);
	}

	char buf[MAX_LINE];  /*缓冲区*/
	int len;             /*行字符个数*/
	while(fgets(buf,MAX_LINE,linefile) != NULL)
	{
		len = strlen(buf);
		buf[len-1] = '\0';  /*去掉换行符*/
/*
		char *word;
		word = (char *)malloc(sizeof(char));
		*word = buf;
		InsertList(List_Content,word);
*/
		//printf("%s %d \n",buf,len - 1);
	}

	ShowList(List_Content,2);
	DropList(List_Content);

	
	return 0;
}
