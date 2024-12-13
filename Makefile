all : img_proc.o main.o
	g++ -g img_proc.o main.o

main.o : main.c
	g++ -c main.c -g

img_proc.o : img_proc.cpp
	g++ -c img_proc.cpp -g

clean :
	rm -rf *.o a.out .*.*.swp
