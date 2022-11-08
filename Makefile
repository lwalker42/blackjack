CC := g++
CFLAGS := -Wall -Wextra 
SRC := ./src
OBJDIR := ./obj
INC := -I $(SRC)
ALL := $(wildcard $(SRC)/*.cpp)
MAINS := $(SRC)/blackjack.cpp $(SRC)/stats.cpp $(SRC)/simulation.cpp $(SRC)/test.cpp
FILTERED := $(filter-out $(MAINS), $(ALL))
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJDIR)/%.o, $(FILTERED))


blackjack: $(OBJDIR)/blackjack.o $(OBJS) | build
	$(CC) $(CFLAGS) -o build/$@ $(INC) $^

stats: $(OBJDIR)/stats.o $(OBJS) | build
	$(CC) $(CFLAGS) -o build/$@ $(INC) $^

simulation: $(OBJDIR)/simulation.o $(OBJS) | build
	$(CC) $(CFLAGS) -o build/$@ $(INC) $^

test: $(OBJDIR)/test.o $(OBJS) | build
	$(CC) $(CFLAGS) -DDEBUG -o build/$@ $(INC) $^


$(OBJDIR)/%.o: $(SRC)/%.cpp | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p $@

build:
	mkdir -p $@

clean:
	rm -rf build/
	rm -rf obj/
