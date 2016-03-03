#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a='b';
	char *b = "abcd";
	int x;
	printf("%d\n",a);
	x = (int)a;
	printf("%d\n",x);
	printf("%c\n",b[2]);

	return 0;
}
