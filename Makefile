# Makefile

# igual indica atribuição de variavel

CPP = g++
CPPFLAGS = -Wall -Wconversion

OBJ = main.o Jogada.o

# dois pontos indica dependencia
main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o main

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o

Jogada.o: Jogada.cpp
	$(CPP)  $(CPPFLAGS) -c Jogada.cpp -o Jogada.o

all: main

clean:
	rm -f *.o
