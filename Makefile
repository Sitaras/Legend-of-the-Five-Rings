PLAYER=./Player
CARDS=./Cards
DECKBUILDER=./DeckBuilder
GAMEBOARD=./Gameboard
TYPECONVERTER=./TypeConverter
STATISTICS=./Statistics

CC=g++
CXXFLAGS = -g -Wall -I$(PLAYER) -I$(CARDS) -I$(DECKBUILDER) -I$(GAMEBOARD) -I$(TYPECONVERTER) -I$(STATISTICS) -std=c++11

OBJ=main.o $(PLAYER)/Player.o $(CARDS)/Cards.o $(DECKBUILDER)/DeckBuilder.o $(GAMEBOARD)/Gameboard.o $(TYPECONVERTER)/TypeConverter.o $(STATISTICS)/Statistics.o

EXEC=project

all: $(EXEC)
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXEC)
