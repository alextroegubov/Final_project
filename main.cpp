#include "game.h"
#include "player.h"
#include <thread>


int main(){
	Gameboard game;
	Player p1, p2;
	
	game.Draw();
	game.ShuffleDeck();

	int i = 0;
	while(i < 30){
		std::this_thread::sleep_for(std::chrono::seconds(1));
		p1.DrawCard(game.GetCardFromDeck());
		game.Draw();
		i++;
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));
	return 0;
};