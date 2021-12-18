exec:binarycode.o
	g++ binarycode.o -o main -L/usr/include/postgresql/lib -lpq
binarycode.o:DBClasses_preprocessed.h exceptions.h main.cpp
	g++ -o binarycode.o -c main.cpp -I/usr/include/postgresql
DBClasses_preprocessed.h:DBClasses.h
	g++ -E DBClasses.h -o DBClasses_preprocessed.h -I/usr/include/postgresql
.PHONY: clean
clean:
	rm *.o
