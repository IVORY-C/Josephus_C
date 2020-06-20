SHELL=cmd.exe
objects = main.o person.o josephus.o readers.o

main:$(objects)
	gcc -o main $(objects)

main.o : main.c
	gcc -c main.c

person.o : include/person.h 
	gcc -c src/person.c	

josephus.o : include/josephus.h include/person.h
	gcc -c src/josephus.c
	
readers.o : include/readers.h include/person.h include/josephus.h
	gcc -c src/readers.c


.PHONY : clean
clean:
	del *.o -rf


