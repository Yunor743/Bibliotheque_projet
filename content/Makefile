%.o : %.cpp *.hpp
	g++ -std=c++1z -c $@ $< -O3 -Wall -Wextra -Wpedantic

all : *.o
	g++ -std=c++1z -o index.exe $^ -O3