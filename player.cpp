#include "player.h"
#include "ui.h"
#include "algorithm"
#include <cassert>

Player::Player(){
	cards_.resize(10);
}

int Player::CalculateScore(){
	return 0;
}

void Player::AddCard(Card* card){
	assert(card);

	cards_[card->type_].push_back(card);

	std::sort(cards_[card->type_].begin(), cards_[card->type_].end());

	//do smth with borders and card position
//	sf::Vector2f pos = {50 /*+  card->size_.x / 2*/, 768 - 300 /*+ card->size_.y / 2*/}; 

//	int vert_offset = 0;

	Ui::Get()->SetCardForPlayer(0, cards_[card->type_]);

/*	for(auto& item: cards_[card->type_]){
		assert(item);
		item->pos_ = {pos.x + 120 * (card->type_), pos.y + vert_offset};
		item->sprite_.setPosition(item->pos_.x, item->pos_.y);
//		vert_offset += 20; 
	}*/
}

void Player::TakeCards(std::vector<Card*> cards){
	
	for(auto& c: cards)
		AddCard(c);
}