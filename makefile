CXX = g++
PROG = main
CXXFLAGS += -Wall
CXXFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

PROG_OBJ = main.o game.o player.o cards.o
PROG_LIB = game.h player.h cards.h

#PROG_CPP = .cpp

all: $(PROG) clean

$(PROG): $(PROG_OBJ) $(PROG_LIB)
	$(CXX) -o $@ $(PROG_OBJ) $(CXXFLAGS)

#add: $(PROG_LIB) $(PROG_OBJ)
#	git add $(PROG_LIB) $(PROG_CPP)

clean:
	rm -rf *.o