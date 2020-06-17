objects = main.o person.o josephus.o readers.o 

main: $(objects)
	gcc -o main $(objects)

main.o : main.c
	gcc -c main.c
person.o : domain/person.c 
	gcc -c domain/person.c	
josephus.o : domain/josephus.h domain/person.h
	gcc -c domain/josephus.c
readers.o : domain/readers.c domain/person.h domain/josephus.h
	gcc -c domain/readers.c

.PHONY : clean
clean:
	del *.o -rf

