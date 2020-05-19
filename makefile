CXX = g++
PROG = main
CXXFLAGS += -Wall
CXXFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

PROG_OBJ = main.o game.o player.o cards.o texture_manager.o
PROG_LIB = game.h player.h cards.h texture_manager.hpp

#PROG_CPP = .cpp

all: $(PROG)

$(PROG): $(PROG_OBJ) $(PROG_LIB)
	$(CXX) -fsanitize=address -o $@ $(PROG_OBJ) $(CXXFLAGS)

#add: $(PROG_LIB) $(PROG_OBJ)
#	git add $(PROG_LIB) $(PROG_CPP)

clean:
	rm -rf *.o
