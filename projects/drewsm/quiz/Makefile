CFLAGS = -Wall -fpic -coverage -lm -ftest-coverage -fprofile-arcs
	
default: all
	
testme:
	gcc -o testme testme.c -g $(CFLAGS)

runtests: testme
	./testme &> randomquizresult.out

all: testme

clean:
	rm -f *.o randomquizresult.out testme testme.exe *.gcov *.gcda *.gcno *.so *.out
