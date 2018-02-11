Make targets for testme.c include:

all - default target that executes the testme target

testme - builds the testme executable

runtests - use this target to build testme and execute tests.
	Output will be written to randomquizresult.out. Execution
	also gives an error 200, which I  cannot explain, but
	the program executes correctly.

clean - deletes built files, including the randomquizresult.out file

