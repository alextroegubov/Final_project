#include "game.h"
#include "player.h"
#include <thread>


int main(){
	Gameboard game;
	Player p1, p2;
	game.ShuffleDeck();
	game.AddPlayer(&p1);
	game.Run();
	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return 0;
};