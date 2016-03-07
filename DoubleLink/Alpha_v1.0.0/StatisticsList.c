#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct{
	char *word;
	int num;	
	int length;
}Wordnum[1000000];

char *GetFileContent(char *filename)
{
	FILE *novelfile;
	int i = 0,j = 0,word;
	char *data[1000000];
	char str[100];

	if((novelfile = fopen(filename,"r")) == NULL)
	{
		printf("ERROR! File can't be Opened!\n");
		exit(1);
	}
	while(( word = fgetc(novelfile)) != EOF)	//判断文件是否结束
	{
		//if( word != ' ' && word != '\n' && word != ',' && word != '.' && word != '\'' && word != '\t' && word != '\r')
		if((word > 64 && word < 91) || (word > 96 && word < 123))
		{
			str[i] = (char)word;
			i++;
		}
		else
		{
			if(strlen(str) == 0 )
				continue;

			//printf("%d have NULL\n",j);
			//printf("%s\n",str);
			
			data[j] = str;
			Wordnum[j].word = str;
			Wordnum[j].num = 0;
			Wordnum[j].length = strlen(str);
			//Wordnum[j] = {str, 0, strlen(str)};
			j = j + 1;
			i = 0;
			
			memset(str,'\0',sizeof(str));
		}
	}
	data[j] = NULL;

	return *data;
}


int main()
{

	char *filename = "LittleTest.txt";
	//char *filename = "Harry Potter and the Order of the Phoenix.txt";
	char *data[1000000];
	*data = GetFileContent(filename);
	int i = 0;

	while(1)
	{
		if(data[i] == NULL)
			break;
		//printf("%s\n",data[i]);
		printf("%s %d\n",Wordnum[i].word,Wordnum[i].length);
		i++;
	}
	return 0;
}
