all: cal

cal: cal.o main.o
	g++ -o cal cal.o main.o

cal.o: cal.cpp
	g++ -c cal.cpp

main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm -f cal
	rm -f *.o
