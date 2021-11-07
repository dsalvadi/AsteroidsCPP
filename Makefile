CC = g++
CXXFLAGS  = -g -Wall -Wextra

all: Game.o MainMenu.o main.o main

Game.o: Game.cpp
	$(CC) $(CXXFLAGS) -MMD -c Game.cpp -I src/include

MainMenu.o: MainMenu.cpp
	$(CC) $(CXXFLAGS) -MMD -c MainMenu.cpp -I src/include

main.o: main.cpp
	$(CC) $(CXXFLAGS) -MMD -c main.cpp -I src/include

main: main.o Game.o MainMenu.o
	$(CC) $(CXXFLAGS) -MMD main.o Game.o MainMenu.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

