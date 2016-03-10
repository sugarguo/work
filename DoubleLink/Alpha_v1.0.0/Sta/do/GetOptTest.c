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
#include <time.h>
#include "DoubleLink.h"

#define MAX_LINE 1024

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
	FILE *fp = NULL;
	DLNode *p = NULL;
	int i = 1;

	if((fp = fopen("dat.txt","w")) == NULL)
	{
		printf("ERROR! File can't be Opened!\n");
		exit(1);
	}

	p = List_Content->next;
	while(p->next != List_Content)
	{
		if( strcasecmp((char *)p->data , (char *)p->next->data) == 0)
			i++;
		else
		{
			//printf("Word : %s\t\t\t\t  Show : %d \n",(char *)p->data,i);
			fprintf(fp,"Word :\t%-20s\t|\tShow :\t%-20d \n",(char *)p->data,i);
	
			i = 1;
		}
		p = p->next;
	}
	//free(p);
	printf("\n\nDat.txt Write OK!Please See it!\n\n\n");
	fclose(fp);
}

DLNode *GetFileContent(DLNode *List_Content, char *filename)
{
	FILE *novelfile,*fp;
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
			str[i] = (char)tolower(word);
			i++;
		}
		else
		{
			if(strlen(str) == 0 )
				continue;
			str[i] = '\0';
			//printf("%s\n",*wordstr);
			char *wordstr = NULL;
			wordstr = (char *)malloc((strlen(str) + 1) * sizeof(char));
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
				//wordstr=NULL;
				//free(wordstr);
			}
		}
	}
	fclose(novelfile);
	//ShowList(List_Content,2);
	return List_Content;
}

int GetStatistics(char *filename, int hflag, int pflag)
{
	DLNode *List_Content = NULL;

	List_Content = CreateList();

	if (List_Content == NULL)
	{
		printf("Error!\n");
		exit(1);
	}
	else
		printf("OK!Create OK!\n");

	int start_time = 0, end_time = 0;

	start_time = clock();
	GetFileContent(List_Content,filename);
	end_time = clock();
	printf("Read time :  %f \n", (float)(end_time - start_time) / CLOCKS_PER_SEC  );

	start_time = clock();
	if(hflag == 0)
		SequenceList(List_Content, 1, CallBackCmpStr_K);
	else
		SequenceList(List_Content, 2, CallBackCmpStr);
	end_time = clock();
	printf("Sequence time :  %f \n", (float)(end_time - start_time) / CLOCKS_PER_SEC  );

	if(pflag == 0)
		ShowList(List_Content, 2, 0);
	start_time = clock();
	StatisticsContent(List_Content);
	end_time = clock();
	printf("Statistics time : %f \n", (float)(end_time - start_time) / CLOCKS_PER_SEC  );

	DropList(List_Content);
	
	return 0;

}


int getLine(char *filename)
{
	FILE *fp;
	int line;
    if(NULL == (fp = fopen(filename, "r")))  
    {  
        printf("File open ERROR\n");  
        exit(1);  
    }
	char ch;
    while(EOF != (ch=fgetc(fp)))  
    {  
        line++; 
    }  
  
    fclose(fp);  
  
    return line;  
}

int main(int argc, char **argv)
{
	int oc = 0;
	char ec = NULL;
	char *b_opt_arg = NULL;

	while((oc = getopt(argc, argv, "f:plsh")) != -1)
	{
		switch(oc)
		{
			case 'f':
				b_opt_arg = optarg;
				printf("Filename(with path): %s\n", optarg );
				break;
			case 'p':
				printf("Print ALL Statistics num:\n");
				break;
			case 's':
				printf("Print Sequence:\n");
				break;
			case 'l':
				printf("FILE line num:\n");
				break;
			case 'h':
				printf("High Statistics:\n");
				break;
			case '?':
				ec = (char)optopt;
				printf("Arguments ERROR!\n\' %c \' Not Support!\nOnly f:filename p l n\n", ec);
				break;
			case ':':
				printf("Don't have parameter!\nPlease check!\n");
				break;
		}
	
	}
	return 0;
}
