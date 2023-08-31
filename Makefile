project: database.o user_interface.o
	gcc user_interface.o database.o -o project

user_interface.o: user_interface.c record.h database.c
	gcc -ansi -pedantic-errors -Wall -c user_interface.c

database.o: database.c record.h 
	gcc -ansi -pedantic-errors -Wall -c database.c
