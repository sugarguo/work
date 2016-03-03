#*****************************************************************************

# Copyright        :  

#

# Author           :   sugarguo

# Date             :   2016-03-01

# Version          :   Link静态链接库

# Description 	   :   DoubleLinkTestMakefile

#

#****************************************************************************/

CC = gcc

AR = ar rc

DoubleLinkTest : DoubleLinkTest.o DoubleLinkTest.a
	$(CC)	-o	DoubleLinkTest DoubleLinkTest.o

DoubleLinkTest.o : DoubleLinkTest.c
	$(CC)	-c	DoubleLinkTest.c
DoubleLinkTest.a : DoubleLink.h
	$(AR)	-c	DoubleLink.o DoubleLink.h

.PHONY: clean
clean :
	$(RM) = rm -fr *.o *.a
