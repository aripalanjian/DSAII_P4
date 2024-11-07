CFLAGS = -g -Wall
CC = g++

objects = main.o brute.o bin.o heuristic.o

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.cpp brute.cpp bin.cpp heuristic.cpp

.PHONY : clean
clean:
	rm -f main $(objects)
	rm -f *.exe
	rm -f errReport.txt