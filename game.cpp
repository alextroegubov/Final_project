#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>

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
	//TO DO: cut correctly from textures

	//puttng cards in the deck
	deck_.resize(c_manager_.cards.size());
	
	for(int i = 0; i < deck_.size() - 1; i++){
		deck_[i] = &c_manager_.cards[i];
	}
	//
	for(auto& card: c_manager_.cards){
		//pos in sprite, size
		card.size_ = basic_size;
		card.sprite_.setTextureRect(sf::IntRect({300, 300}, card.size_)); ///////<<<<---------
		card.sprite_.setOrigin(card.size_.x / 2, card.size_.y / 2); 
		card.sprite_.setColor(sf::Color::Red);
		card.sprite_.setPosition(deck_pos);
	}

	//setting table;
	table_sprite_.setTexture(t_manager_.Get(TextureManager::Table));
	table_sprite_.setTextureRect(sf::IntRect({0,0}, {width, height}));
}

Gameboard::~Gameboard(){
	Finish();

	delete window_;
}

void Gameboard::Finish(){
	is_done_ = true;
	window_->close();
}


std::random_device rd;
std::mt19937 g(rd());

void Gameboard::Shuffle(std::vector<Card*> deck){
	std::shuffle(deck.begin(), deck.end(), g);
}


void Gameboard::Draw(){

	window_->clear();

	window_->draw(table_sprite_);

	for(const auto& card: c_manager_.cards){
		window_->draw(card.sprite_);
	}

	window_->display();
}