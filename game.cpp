#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>

Gameboard::Gameboard(){//:
	Init();
}

void Gameboard::CreateCards(){

	std::vector<Card::CardType> types = {Card::Cannon, Card::Anchor, Card::Hook, Card::Key, Card::Chest, 
										 Card::Scroll, Card::CrystalBall, Card::Sabre, Card::Kraken};
	//adding all types exept mermaid
	for(int points = 2; points <= 7; points++){
		for(auto& t: types){
			card_holder_.push_back(std::move(Card(t, points, sf::Sprite(t_manager_.Get(t)), Card::abilities[t])));
		}		
	}

	//adding mermaid
	Card::CardType m = Card::Mermaid; 
	for(int points = 4; points <= 9; points++){
		card_holder_.push_back(std::move(Card(m, points, sf::Sprite(t_manager_.Get(m)), Card::abilities[m])));
	}
	assert(card_holder_.size() == 60);

	//puttng cards in the deck
	deck_.resize(card_holder_.size());

	for(size_t i = 0; i < deck_.size(); i++){
		deck_[i] = &(card_holder_.at(i));
		assert(deck_.at(i));
	}
	assert(deck_.size() == 60);
}

void Gameboard::Init(){

	window_ = new sf::RenderWindow(sf::VideoMode(width, height), "Dead Man's Draw", sf::Style::Default);
	assert(window_);

	t_manager_.LoadAll();

	CreateCards();
	
	for(auto& card: card_holder_){

		card.size_ = {740, 1030};
		sf::Vector2i pos_in_tex;

		if(card.type_ == Card::Mermaid)
			pos_in_tex = {(card.points_ - 4) * card.size_.x, 0};
		else
			pos_in_tex = {(card.points_ - 2) * card.size_.x, 0};

		card.sprite_.setTextureRect(sf::IntRect(pos_in_tex, card.size_)); ///////<<<<---------
		card.sprite_.scale(0.15f, 0.15f);
		card.sprite_.setPosition(deck_pos);
	}

	//setting backstage
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


Card* Gameboard::GetCardFromDeck(){
	Card* card = deck_.back();
	assert(card);
	deck_.pop_back();

	return card;
}


std::random_device rd;
std::mt19937 g(rd());

void Gameboard::ShuffleDeck(){
	std::shuffle(deck_.begin(), deck_.end(), g);
}


void Gameboard::Draw(){
	assert(window_);

	window_->clear();

	window_->draw(table_sprite_);

	for(const auto& card: card_holder_){
		window_->draw(card.sprite_);
	}

	window_->display();
}