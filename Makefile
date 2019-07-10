# Makefile

# igual indica atribuição de variavel

CPP = g++
CPPFLAGS = -Wall -Wconversion

OBJ = main.o hash.o

# dois pontos indica dependencia
main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o main

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o

hash.o: hash.cpp
	$(CPP)  $(CPPFLAGS) -c hash.cpp -o hash.o

all: main

clean:
	rm -f *.o main
