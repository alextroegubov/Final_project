#pragma once

#include <vector>
#include "cards.h"

class Player{
public:
	Player();
	int CalculateScore();

	void AddCard(Card* card);

	void TakeCards(std::vector<Card*>);
	//only top cards
	Card* GetCard(sf::Vector2i ms_p);

	bool HasCards();

private:
	std::vector<std::vector<Card*>> cards_;
};
