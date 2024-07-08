FILES_TO_ZIP = Makefile main.cpp stream.cpp block.cpp stream.h block.h

output: main.o block.o stream.o
	g++ main.o block.o stream.o -o cipher.


main.o: main.cpp
	g++ -c main.cpp

block.o: block.cpp block.h
	g++ -c block.cpp

stream.o : stream.cpp stream.h
	g++ -c stream.cpp

clean:
	rm *.o cipher

zip: 
	tar -czvf ../Pavilonis-Quintin-PA1.tar.gz $(FILES_TO_ZIP)