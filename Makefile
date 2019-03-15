

exec: run
	./runnable

run: proposeAndRejectAlgorithm main 
	g++ main.o proposeAndRejectAlgorithm.o -o runnable

proposeAndRejectAlgorithm: proposeAndRejectAlgorithm.cpp
	g++ -c proposeAndRejectAlgorithm.cpp

main: main.cpp
	g++ -c main.cpp
clean:
	rm *.o
