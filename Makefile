SHELL=cmd.exe

objects = person.o josephus.o readers.o
test_objects = cbehave.o test_person.o test_josephus.o test_readers.o 

main : main.o $(objects) 
	gcc -o main main.o $(objects)

tests : $(objects) $(test_objects)
	gcc -o tests $(objects) $(test_objects)

main.o : main.c
	gcc -c main.c

person.o : include/person.h 
	gcc -c src/person.c	

josephus.o : include/josephus.h include/person.h
	gcc -c src/josephus.c
	
readers.o : include/readers.h include/person.h include/josephus.h
	gcc -c src/readers.c

cbehave.o : tests/cbehave/cbehave.h
	gcc -c tests/cbehave/cbehave.c

test_person.o : 
	gcc -c tests/test_person.c	

test_josephus.o : 
	gcc -c tests/test_josephus.c
	
test_readers.o : 
	gcc -c tests/test_readers.c

.PHONY : clean
clean:
	del *.o -rf


