%.o : %.cpp *.hpp
    g++ -c -o $@ $< -O3 -Wall -Wextra -Wpedantic

all : *.o
    g++ -o index.exe $^ -O3