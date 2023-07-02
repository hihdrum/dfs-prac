all : dfs bws

dfs : dfs.c
	gcc -Wall dfs.c -o dfs

bws : bws.c
	gcc -Wall bws.c -o bws

.PHONEY : clean
clean:
	rm -rf a.out dfs bws
