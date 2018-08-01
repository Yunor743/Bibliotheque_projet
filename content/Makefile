%.o : %.cpp *.hpp
	g++ -c -o $@ $<

all : *.o
	g++ -o index.exe $^

	.PHONY clean

clean:
	rm -rf *.o