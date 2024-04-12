all: sort

sort: sort.cpp
	g++ -o sort sort.cpp -fopenmp -lpthread -ltbb --std=c++17 -O3 -march=native -latomic -lz -lm
clean:
	rm -f sort