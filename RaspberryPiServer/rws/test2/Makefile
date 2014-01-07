build: test

JFile.o: ../file/JFile.cpp
	cp ../file/JFile.hpp .
	g++ -c $<

test: test.o JFile.o
	g++ -o test test.o JFile.o
	make clean

test.o: test.cpp
	g++ -c $<

clean:
	rm test.o
	rm JFile.o
