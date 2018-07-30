%.o : %.cpp *.hpp
    g++ -c -o $@ $< -O3 -Wall -Wextra -Wpedantic
	
index : %.o
    g++ -o $@ $^ -O3