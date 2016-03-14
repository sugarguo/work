#/**
* @file			LsDoubleLink.c
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
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include "DoubleLink.h"

///@brief 定义默认信息的结构体
struct globalArgs_t{
	char *filename;			///<默认数据的文件名
	char *outfilename;		///<默认输出的文件名
	int hflag;				///<是否快速排序的flag
	int sflag;				///<是否显示排序结果的flag
	int pflag;				///<是否显示最终结果的flag
	int lflag;				///<是否显示行号的flag
	int oflag;				///<是否采用默认文件的flag
	int fflag;				///<是否采用默认文件的flag
	int lines;				///<数据文件的行数
	int words;				///<数据文件中拥有词数
	int allwords;			///<数据文件中总词数
	int bytes;				///<数据文件中字节数
}globalArgs;

static const char *optString = "hplso:v?";

struct FileInfo
{
	char *filename;
	int bytes;
	char *ctime;
	char *mtime;
	char *atime;
};


void CallBackShowFileInfo(struct FileInfo *data)
{
	printf("filename: %s , bytes: %d , ctime: %s",data->filename,data->bytes,data->ctime);
}


char *FromUidToUserName(uid_t uid)
{
	struct passwd *pwd;
	pwd = getpwuid(uid);
	//printf("username : %s \n", pwd->pw_name);
	return (char *)pwd->pw_name;
}


char BackModeType(mode_t st_mode)
{
	if ((st_mode & S_IFSOCK) == S_IFSOCK)
		return 's';
	else if((st_mode & S_IFREG) == S_IFREG)
		return '-';
	else if((st_mode & S_IFDIR) == S_IFDIR) //S_ISDIR(statbuf.st_mode)
		return 'd';
	else if((st_mode & S_IFLNK) == S_IFDIR)
		return 'l';
	else if((st_mode & S_IFBLK) == S_IFDIR)
		return 'b';
}


int BackModeCompetence(mode_t st_mode)
{
	int userrwx = 0;
	int grouprwx = 0;
	int otherrwx = 0;

	if ((st_mode & S_IRUSR) == S_IRUSR)
		userrwx += 4;
	if ((st_mode & S_IWUSR) == S_IWUSR)
		userrwx += 2;
	if ((st_mode & S_IXUSR) == S_IXUSR)
		userrwx += 1;


	if ((st_mode & S_IRGRP) == S_IRGRP)
		grouprwx += 4;
	if ((st_mode & S_IWGRP) == S_IWGRP)
		grouprwx += 2;
	if ((st_mode & S_IXGRP) == S_IXGRP)
		grouprwx += 1;


	if ((st_mode & S_IROTH) == S_IROTH)
		otherrwx += 4;
	if ((st_mode & S_IWOTH) == S_IWOTH)
		otherrwx += 2;
	if ((st_mode & S_IXOTH) == S_IXOTH)
		otherrwx += 1;

	return userrwx * 100 + grouprwx * 10 + otherrwx; 
}


char *BackAllTime(char timeback[], time_t time)
{
	//char timeback[128] = "2016/03/11 11:11:11";
	//timeback = (char *)malloc(sizeof(char))
	strftime(timeback,128,"%Y/%m/%d %H:%M:%S\n",localtime(&time));
	printf("The Time is :%s",timeback);
	return timeback;
}


int main(int argc, char **argv)  
{  
	DIR *dirptr = NULL;  
	struct dirent *entry;  
	struct stat buf;
	struct FileInfo fileinfo;
	char timeback[128] = "2016/03/11 11:11:11";

	DLNode *List = NULL;

	List = CreateList();


	if (argc != 2) {
		argv[1] = ".";
		//printf("Usage：%s filename\n\a", argv[0]);  
		//exit(1);  
	}  

	if((dirptr = opendir(argv[1])) == NULL)  
	{  
		printf("Open Directory %s Error！\n",  argv[1]); 
		return 1;  
	}  
	else  
	{  
		while ((entry = readdir(dirptr)) != NULL)  
		{

			printf("%s\n", entry->d_name);/* 打印出该目录下的所有内容 */  
			fileinfo.filename = entry->d_name;
			stat(entry->d_name,&buf);
			fileinfo.bytes = buf.st_size; 
			fileinfo.ctime = BackAllTime(timeback, buf.st_ctime);
			fileinfo.atime = BackAllTime(timeback, buf.st_atime);
			fileinfo.mtime = BackAllTime(timeback, buf.st_mtime);
			InsertList(List,(void *)&fileinfo);
			printf("file inode : %ld\n", entry->d_ino);
			printf("file size : %d\n", (int)buf.st_size);
			printf("file mode : %d\n", buf.st_mode);
			printf("file link : %d\n", (int)buf.st_nlink);
			printf("file type : %c\n",BackModeType(buf.st_mode) );
			printf("file compet : %d\n",BackModeCompetence(buf.st_mode) );
			printf("file mtime : %s\n",BackAllTime(timeback, buf.st_mtime) );
			printf("file ctime : %s\n",BackAllTime(timeback, buf.st_ctime) );
			printf("file atime : %s\n",BackAllTime(timeback, buf.st_atime) );
			printf("username: %s, userid : %d\n",FromUidToUserName(buf.st_uid), buf.st_uid);

		}  
		closedir(dirptr); 
		
		ShowList(List,0,CallBackShowFileInfo);

		DropList(List);
	}  
	return 0;  
}  
