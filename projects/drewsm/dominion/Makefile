CFLAGS = -Wall -fpic -coverage -lm -ftest-coverage -fprofile-arcs -O0
	
default: all
	
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unitTestCommon.o: unitTestCommon.c unitTestCommon.h
	gcc -c unitTestCommon.c -g $(CFLAGS)

test1: unittest1.c dominion.o rngs.o unitTestCommon.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o unitTestCommon.o $(CFLAGS)
	
test2: unittest2.c dominion.o rngs.o unitTestCommon.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o unitTestCommon.o $(CFLAGS)
	
test3: unittest3.c dominion.o rngs.o unitTestCommon.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o unitTestCommon.o $(CFLAGS)
	
test4: unittest4.c dominion.o rngs.o unitTestCommon.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o unitTestCommon.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o rngs.o unitTestCommon.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o unitTestCommon.o $(CFLAGS)
	
unittestsall: test1 test2 test3 test4 cardtest1
	./unittest1 &> unittestresults.out
	gcov -bf unittest1 dominion >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -bf unittest2 dominion >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -bf unittest3 dominion >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -bf unittest4 dominion >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -bf cardtest1 dominion >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	
randTestCommon.o: dominion.o rngs.o interface.o
	gcc -c randTestCommon.c randTestCommon.h -g dominion.o rngs.o interface.o $(CFLAGS)
	
randomtestadventurer: randTestCommon.o dominion.o rngs.o interface.o
	gcc -o randomtestadventurer -g randomtestadventurer.c randTestCommon.h -g randTestCommon.o dominion.o rngs.o interface.o $(CFLAGS)
	
randomtestcard1: randTestCommon.o dominion.o rngs.o interface.o
	gcc -o randomtestcard1 -g randomtestcard1.c randTestCommon.h -g randTestCommon.o dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard2: randTestCommon.o dominion.o rngs.o interface.o
	gcc -o randomtestcard2 -g randomtestcard2.c randTestCommon.h -g randTestCommon.o dominion.o rngs.o interface.o $(CFLAGS)
	
randomtestall: randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestadventurer &> randomtestadventurer.out
	gcov -bf randomtestadventurer dominion >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	./randomtestcard1 &> randomtestcard1.out
	gcov -bf randomtestcard1 dominion >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out
	./randomtestcard2 &> randomtestcard2.out
	gcov -bf randomtestcard2 dominion >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out
	

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o dominion.o rngs.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard test1 test2 test3 test4 randomtestadventurer randomtestcard1

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 randomtestadventurer randomtestcard1 randomtestcard2 dominion
