#pragma once

#include <vector>

#include "cards.h"
#include "player.h"

class Gameboard{
public:
	void StartGame();
	void ShuffleDeck();
	void ShuffleDiscard();
	void DrawCard();
	void DiscardGameArea();
	void Finish();

private:
	std::vector<Card*> discard_;
	std::vector<Card*> game_area_;
	std::vector<Card*> deck_;
	std::vector<Player*> players_;
};