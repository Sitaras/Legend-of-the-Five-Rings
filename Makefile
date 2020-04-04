CC=g++
CFLAGS = -g -Wall

project: Player.cpp Cards.cpp DeckBuilder.cpp main.cpp Gameboard.cpp TypeConverter.cpp Statistics.cpp
	$(CC) $(CFLAGS) -std=c++11 -o project Player.cpp Cards.cpp DeckBuilder.cpp main.cpp  TypeConverter.cpp Gameboard.cpp Statistics.cpp


clean:
	rm -f project
