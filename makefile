CXX = g++
PROG = main
CXXFLAGS += -Wall
CXXFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

PROG_OBJ = main.o game.o player.o cards.o texture_manager.o ui.o abilities.o sound_manager.o
PROG_LIB = game.h player.h cards.h texture_manager.hpp ui.h sound_manager.hpp

#PROG_CPP = .cpp

all: $(PROG)

$(PROG): $(PROG_OBJ) $(PROG_LIB)
	$(CXX) -fsanitize=address -o $@ $(PROG_OBJ) $(CXXFLAGS)

#add: $(PROG_LIB) $(PROG_OBJ)
#	git add $(PROG_LIB) $(PROG_CPP)

clean:
	rm -rf *.o
