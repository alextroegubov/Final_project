#pragma once

#include <vector>
#include "cards.h"

class Player{
public:
	Player();
	int CalculateScore();

	void DrawCard(Card* card);
	
private:
	std::vector<std::vector<Card*>> cards_;
};