all: irondelle

irondelle: *.o
	g++ -o $@ $^

%.o: %.cpp *.hpp
	g++ -c $*.cpp

.PHONY: clean

clean:
	rm -rf *.o