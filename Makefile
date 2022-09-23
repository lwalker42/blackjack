CC = g++
DIR = ./src
CFLAGS = -I $(DIR)
FILES = ./src/*.cpp

blackjack: $(FILES)
	$(CC) -o build/$@ -I $(DIR) $?

.cpp.o:
	$(CC) $(CFLAGS) -c $(DIR)/$*.cpp

blackjack.o: ./src/blackjack.cpp ./src/blackjack.hpp 
	$(CC) -c $(DIR)/blackjack.cpp
