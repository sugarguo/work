#include <stdio.h>
#include <stdlib.h>

int CmpStr(const void *one, const void *two)
{
	printf("cmp : %s %s\n",*(char **)one,*(char **)two);
	return(strcmp(*(char **)one, *(char **)two));
}

int main()
{
	int i = 0;
	char *list[] = {"Harry","Potter", "and", "the", "Order", "of" ,"the", "Phoenix", "harry", "potter"};

	qsort(list, 10, sizeof(char *), CmpStr);
	for(i = 0; i < 10; i++)
		printf("word : %s\n", list[i]);

	return 0;

}
