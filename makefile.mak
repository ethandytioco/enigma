# Makefile for enigma project

# we need rotor.o and enigma_m3.o to make enigma
enigma: rotor.o enigma.o main.o
	g++ rotor.o enigma.o main.o -o enigma

# we need rotor.cpp to make rotor.o
rotor.o: rotor.cpp
	g++ -c rotor.cpp

# we need enigma_m3.cpp to make enigma.o
enigma.o: enigma.cpp
	g++ -c enigma.cpp

# we need main.cpp to make main.o
main.o: main.cpp
	g++ -c main.cpp

# cleans out files with out and .o extensions
clean:
	rm -f *.out *.o enigma