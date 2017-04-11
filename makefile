FLAGS = -Wall -Wextra -std=c99

dijkstra: dijkstra.o binomial.o darray.o vertex.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o
	gcc $(FLAGS) dijkstra.o binomial.o darray.o vertex.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o -o dijkstra
dijkstra.o: dijkstra.c binomial.c darray.c vertex.c scanner.c comparator.c integer.c real.c string.c queue.c sll.c
	gcc $(FLAGS) -c dijkstra.c
binomial.o: binomial.c binomial.h
	gcc $(FLAGS) -c binomial.c
darray.o: darray.c darray.h
	gcc $(FLAGS) -c darray.c
vertex.o: vertex.c vertex.h
	gcc $(FLAGS) -c vertex.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
comparator.o: comparator.c comparator.h
	gcc $(FLAGS) -c comparator.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
cleanbuild:
	clear
	make clean
	make
clean:
	rm -f dijkstra.o binomial.o darray.o vertex.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o dijkstra

test: ./dijkstra

	./dijkstra single.0 > myOutSingle.txt
	./dijkstra two.0 > myOutTwo.txt
	./dijkstra unweighted.0 > myOutUnweighted.txt
	./dijkstra g6.0 > myOutG6.txt
	./dijkstra g7.0 > myOutG7.txt
	./dijkstra g8.0 > myOutG8.txt
	./dijkstra g9.0 > myOutG9.txt
	./dijkstra g10.0 > myOutG10.txt
	./dijkstra g11.0 > myOutG11.txt
	./dijkstra g12.0 > myOutG12.txt
	./dijkstra g13.0 > myOutG13.txt
	./dijkstra g14.0 > myOutG14.txt
	./dijkstra g15.0 > myOutG15.txt
	diff outSingle.txt myOutSingle.txt
	diff outTwo.txt myOutTwo.txt
	diff outUnweighted.txt myOutUnweighted.txt
	diff outG6.txt myOutG6.txt
	diff outG7.txt myOutG7.txt
	diff outG8.txt myOutG8.txt
	diff outG9.txt myOutG9.txt
	diff outG10.txt myOutG10.txt
	diff outG11.txt myOutG11.txt
	diff outG12.txt myOutG12.txt
	diff outG13.txt myOutG13.txt
	diff outG14.txt myOutG14.txt
	diff outG15.txt myOutG15.txt
