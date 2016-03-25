#****************************************************************************

# Copyright        :   EmbedWay 恒为科技武汉研发中心 By:Sugarguo

# Author           :   sugarguo

# Date             :   2016-03-01

# Version          :   Link静态链接库

# Description 	   :   DoubleLinkTestMakefile

#

#****************************************************************************/

CC = gcc

AR = ar rcs

RM = rm -fr *.o *.a *.out

ThreadTest : ThreadTest.o libDoubleLink.a 
	$(CC)	-o	ThreadTest ThreadTest.o libDoubleLink.a 

ThreadTest.o : ThreadTest.c DoubleLink.h 
	$(CC)	-c	ThreadTest.c

libDoubleLink.a : DoubleLink.o
	$(AR)		libDoubleLink.a DoubleLink.o

DoubleLink.o :  DoubleLink.c
	$(CC)	-c	DoubleLink.c


.PHONY: clean
clean :
	$(RM)		ThreadTest
