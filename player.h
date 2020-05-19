#pragma once

#include <vector>
#include "cards.h"

class Player{
public:
	Player();
	int CalculateScore();

	void AddCard(Card* card);

	void TakeCards(std::vector<Card*>);
	
private:
	std::vector<std::vector<Card*>> cards_;
};