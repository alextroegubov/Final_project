#include "game.h"
#include "player.h"
#include "thread"
int main(){
	Gameboard game;
	Player p1, p2;
	int i = 0;
	
	game.Draw();

	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
};