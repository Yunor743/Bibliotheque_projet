%.o : %.cpp *.hpp
	g++ -std=c++1z -c -o $@ $< -O3 -Wall -Wextra -Wpedantic

all : *.o
	g++ -o index.exe $^ -O3