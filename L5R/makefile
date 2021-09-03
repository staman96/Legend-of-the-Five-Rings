CC = g++

L5R: main.o TypeConverter.o DeckBuilder.o GameBoard.o Player.o cards/Card.o cards/Follower.o cards/Holding.o cards/Personality.o cards/Item.o cards/BlackCards.o cards/GreenCards.o
	$(CC) -g main.o TypeConverter.o DeckBuilder.o GameBoard.o Player.o cards/Card.o cards/Follower.o cards/Holding.o cards/Personality.o cards/Item.o cards/BlackCards.o cards/GreenCards.o -o L5R

Card.o: cards/Card.cpp cards/Card.h
	$(CC) -c -g cards/Card.cpp cards/

Follower.o: cards/Follower.cpp cards/Card.h cards/Follower.h
	$(CC) -c -g cards/Follower.cpp cards/

Holding.o: cards/Holding.cpp cards/Card.h cards/Holding.h
	$(CC) -c -g cards/Holding.cpp cards/

Personality.o: cards/Personality.cpp cards/Card.h cards/Personality.h cards/Item.h cards/Follower.h
	$(CC) -c -g cards/Personality.cpp cards/

Item.o:  cards/Item.cpp cards/Card.h cards/Item.h
	$(CC) -c -g cards/Item.cpp cards/

BlackCards.o: cards/BlackCards.cpp cards/BlackCards.h cards/Holding.h cards/Personality.h
	$(CC) -c -g cards/BlackCards.cpp cards/

GreenCards.o: cards/GreenCards.cpp cards/GreenCards.h cards/Item.h cards/Follower.h
	$(CC) -c -g cards/GreenCards.cpp cards/

Player.o: Player.cpp Player.h TypeConverter.h cards/Card.h cards/Follower.h cards/Holding.h cards/Personality.h cards/Item.h cards/BlackCards.h cards/GreenCards.h DeckBuilder.h
	$(CC) -c -g Player.cpp

GameBoard.o: GameBoard.cpp GameBoard.h Player.h DeckBuilder.h cards/BlackCards.h
	$(CC) -c -g GameBoard.cpp 

DeckBuilder.o: DeckBuilder.cpp DeckBuilder.h cards/Card.h cards/BlackCards.h cards/GreenCards.h
	$(CC) -c -g DeckBuilder.cpp

TypeConverter.o: TypeConverter.cpp TypeConverter.h cards/Card.h cards/BlackCards.h cards/GreenCards.h cards/Personality.h cards/Holding.h cards/Follower.h cards/Item.h
	$(CC) -c -g TypeConverter.cpp

main.o: main.cpp TypeConverter.h DeckBuilder.h GameBoard.h Player.h cards/Card.h cards/Follower.h cards/Holding.h cards/Personality.h cards/Item.h cards/BlackCards.h cards/GreenCards.h
	$(CC) -c -g main.cpp

clean:
	rm -rvf *.o L5R cards/*.o