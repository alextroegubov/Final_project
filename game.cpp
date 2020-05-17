#include "game.h"
#include <cassert>


Gameboard::Gameboard():
	window_(nullptr){

	Init();	
}

void Gameboard::Init(){

	window_ = new sf::RenderWindow(sf::VideoMode(width, height), "Best Game", sf::Style::Default);
	assert(window_);

	t_manager_.LoadAll();

	//creating cards
	std::vector<Card::CardType> types = {Card::Cannon, Card::Anchor, Card::Hook, Card::Key, Card::Chest, 
										 Card::Scroll, Card::CrystalBall, Card::Sabre, Card::Kraken};

	for(int points = 2; points <= 7; points++){
		for(auto& t: types){
			c_manager_.cards.push_back(Card(t, points, sf::Sprite(t_manager_.Get(t)), Card::abilities[t]));
		}		
	}

	Card::CardType m = Card::Mermain; 

	for(int points = 4; points <= 9; points++){
		c_manager_.cards.push_back(Card(m, points, sf::Sprite(t_manager_.Get(m)), Card::abilities[m]));
	}

}

Gameboard::~Gameboard(){
	Finish();

	delete window_;
}

void Gameboard::Finish(){
	is_done_ = true;
	window_->close();
}
