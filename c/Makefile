all : dfs bws

dfs : dfs.c edgeInfo.o
	gcc -Wall -MMD dfs.c edgeInfo.o -o dfs

bws : bws.c edgeInfo.o
	gcc -Wall -MMD bws.c edgeInfo.o -o bws

edgeInfo.o : edgeInfo.c
	gcc -Wall -MMD -c edgeInfo.c

.PHONEY : clean
clean:
	rm -f a.out dfs bws *.o *.d

#include *.d
