run: A
	./A metro.txt  Simplon -1 Varenne  
A: main.o metro.o 
	gcc -g -o A main.o metro.o -Wall
metro.o : metro.c metro.h 
	gcc -g metro.c  -c  -Wall

valgrind: 
	valgrind ./A metro.txt  Simplon -1 Varenne 
	
