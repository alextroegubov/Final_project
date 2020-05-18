#include "game.h"
#include "player.h"
#include <thread>


int main(){
	Gameboard game;
	Player p1, p2;
	
	game.Draw();
	game.ShuffleDeck();

	int i = 0;
	while((i++) < 8){
		std::this_thread::sleep_for(std::chrono::seconds(2));
		game.DrawCard();
		game.Draw();
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));
	return 0;
};