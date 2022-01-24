pa3: pa3.o citybst.o
	g++ -o pa3 pa3.o citybst.o

pa3.o: pa3.cpp
	g++ -c -pedantic -Wall -Werror pa3.cpp

citybst.o: citybst.cpp citybst.h
	g++ -c -pedantic -Wall -Werror citybst.cpp

clean:
	rm *.o
