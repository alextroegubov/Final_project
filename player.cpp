#include "player.h"
#include "ui.h"
#include "algorithm"
#include <cassert>

int Player::count = 0;

Player::Player(){

	num_ = count++;
	cards_.resize(10);
}

int Player::CalculateScore(){
	return 0;
}

void Player::AddCard(Card* card){
	assert(card);
	
	card->is_active_ = true;
	
	cards_.at(card->type_).push_back(card);

	std::sort(cards_.at(card->type_).begin(), cards_.at(card->type_).end());

	Ui::Get()->SetCardForPlayer(num_, cards_.at(card->type_));
}

void Player::TakeCards(std::vector<Card*> cards){
	
	for(auto& c: cards)
		AddCard(c);
}


bool Player::HasCards(){

	for(const auto& v: cards_)
		if(v.size() != 0)
			return true;

	return false;
}

const Card* Player::CheckCard(sf::Vector2i ms_pos){
	
	for(auto& v: cards_){
		
		if(v.size() != 0 && v.back()->IsClicked(ms_pos.x, ms_pos.y))
			return v.back();
	}

	return nullptr;
}

Card* Player::GetCard(sf::Vector2i ms_pos){

	for(auto& v: cards_){
		
		if(v.size() != 0 && v.back()->IsClicked(ms_pos.x, ms_pos.y)){
			Card* to_return = v.back();
			v.pop_back();
			return to_return;
		}
	}

	return nullptr;
}


bool Player::HasType(Card::CardType t){

	if(cards_.at(t).empty())
		return false;
	
	return true;
}