#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>

Gameboard::Gameboard():
	win_sz_({1300, 768}),
	is_done_(false){

	deck_pos = 		{(float)win_sz_.x - (CARD_X + DX), 	(float)win_sz_.y / 2 - CARD_Y / 2};
	discard_pos = 	{(float)win_sz_.x - BORDER,  		(float)win_sz_.y / 2 - CARD_Y / 2};

	Init();
}

void Gameboard::CreateWindow(){

	window_ = new sf::RenderWindow(sf::VideoMode(win_sz_.x, win_sz_.y), "Dead Man's Draw", sf::Style::Default);
	assert(window_);
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
		deck_.at(i) = &(card_holder_.at(i));
		assert(deck_.at(i));
	}
	assert(deck_.size() == 60);
}

void Gameboard::Init(){

	t_manager_.LoadAll();

	CreateCards();
	CreateWindow();

	for(auto& card: card_holder_){

		card.size_ = {740, 1030}; //basic size in texture
		sf::Vector2i pos_in_tex;

		if(card.type_ == Card::Mermaid)
			pos_in_tex = {(card.points_ - 4) * card.size_.x, 0};
		else
			pos_in_tex = {(card.points_ - 2) * card.size_.x, 0};

		card.sprite_.setTextureRect(sf::IntRect(pos_in_tex, card.size_)); ///////<<<<---------
		card.sprite_.scale((float)CARD_X / card.size_.x, (float)CARD_Y / card.size_.y);
		card.sprite_.setPosition(deck_pos);
	}

	//setting backstage
	table_sprite_.setTexture(t_manager_.Get(TextureManager::Table));
	table_sprite_.setTextureRect(sf::IntRect({0,0}, win_sz_));
}

Gameboard::~Gameboard(){
	Finish();
	delete window_;
}

void Gameboard::Finish(){
	is_done_ = true;
	window_->close();
}


bool Gameboard::CheckGameArea(Card* card){

	auto b = game_area_.begin();
	auto e = game_area_.end() - 1;
	auto found = std::find_if(b, e, [card](Card* c){return (card->type_ == c->type_);});

	if(found != e){
		std::this_thread::sleep_for(std::chrono::seconds(1));
		DiscardGameArea();
	}
}

Card* Gameboard::DrawCard(){
	//add animation//

	Card* card = deck_.back();
	assert(card);
	deck_.pop_back();
	//20 - between cards, 25 - margin
	card->sprite_.setPosition(	BORDER + (DX + CARD_X) * game_area_.size() , 
								win_sz_.y / 2 - CARD_Y / 2);
//	printf("sprite_pos = (%f, %f)\n", BORDER + (DX + CARD_X) * game_area_.size(), win_sz_.y / 2 - CARD_Y / 2);
	
	game_area_.push_back(card);
	ProcessCard(card);

	return card;
}


std::random_device rd;
std::mt19937 g(rd());

//shuffles cards in deck
void Gameboard::ShuffleDeck(){
	std::shuffle(deck_.begin(), deck_.end(), g);
}

//shuffles cards in discard pill
void Gameboard::ShuffleDiscard(){
	std::shuffle(discard_.begin(), discard_.end(), g);
}

void Gameboard::ProcessCard(Card* card){

	return;
}


//
void Gameboard::DiscardGameArea(){
	for(auto& card: game_area_){
		assert(card);
		discard_.push_back(card);
		card->sprite_.setPosition(discard_pos);
	}

	game_area_.clear();
}


void Gameboard::Run(){

	Card* new_card = nullptr;

	while(!is_done_){

		if(game_area_.size()){
			assert(new_card);
			CheckGameArea(new_card);
		}
		else
			ProcessCard(new_card);

		sf::Event event;
		window_->pollEvent(event);
		
		switch(event.type){
			case sf::Event::Closed:
				Finish();
		}

		new_card = DrawCard();

		std::this_thread::sleep_for(std::chrono::seconds(1));
		
		Draw();
	}
}

//
void Gameboard::Draw(){
	assert(window_);

	printf("deck_pos = (%f,%f)\n", deck_pos.x, deck_pos.y);
	printf("window size = (%lu, %lu)\n", window_->getSize().x,
										 window_->getSize().y);

	window_->clear();

	window_->draw(table_sprite_);

	for(const auto& card: card_holder_){
		window_->draw(card.sprite_);
	}

	window_->display();
}