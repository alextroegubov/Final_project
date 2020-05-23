#pragma once

#include <vector>
#include "cards.h"

class Player{
public:
	static int count;

	Player();
	int CalculateScore();

	void AddCard(Card* card);

	void TakeCards(std::vector<Card*>);
	//only top cards
	Card* GetCard(sf::Vector2i ms_p);
	//
	const std::vector<std::vector<Card*>>& GetCards(){ return cards_;}

	bool HasCards();
	bool HasType(Card::CardType t);

private:
	std::vector<std::vector<Card*>> cards_;
	int num_;
};
