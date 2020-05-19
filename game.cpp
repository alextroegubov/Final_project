#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>

Gameboard::Gameboard():
	win_sz_({1300, 768}),
	is_done_(false),
	act_pl_(0){

	discard_pos = 	{(float)win_sz_.x - CARD_X - BORDER, (float)win_sz_.y / 2 - CARD_Y / 2};
	deck_pos = 		{discard_pos.x - (CARD_X + DX), 	 discard_pos.y};

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

void Gameboard::AddPlayer(Player* p){
	assert(p);

	players_.push_back(p);
}

//
bool Gameboard::CheckGameArea(Card* card){

	auto b = game_area_.begin();
	auto e = game_area_.end() - 1;

	auto duplicate = std::find_if(b, e, [card](Card* c){return (card->type_ == c->type_);});
	auto anchor = std::find_if(b, e, [](Card* c){return (c->type_ == Card::Anchor);});

	if(duplicate != e){
		//found duplicate
		std::this_thread::sleep_for(std::chrono::seconds(1));
		
		if(anchor != e){

			std::vector<Card*> to_take;
			
			for(auto i = b; i != anchor; i++){
				to_take.push_back(*i);
			}	
			game_area_.erase(b, anchor);

			players_.at(act_pl_)->TakeCards(std::move(to_take));
		}
		
		DiscardGameArea();
		return false;
	}

	return true;
}

//
void Gameboard::DiscardGameArea(){
	
	for(auto& c: game_area_){
		assert(c);
		DiscardCard(c);
	}

	game_area_.clear();
}


Card* Gameboard::PutCardInGameArea(){
	
	Card* card = DrawCardFromDeck();
	assert(card);

	card->sprite_.setPosition(	BORDER + (DX + CARD_X) * game_area_.size() , 
								win_sz_.y / 2 - CARD_Y / 2);
	
	game_area_.push_back(card);

	return card;
}

//gets the top card from discard pill
Card* Gameboard::DrawCardFromDiscard(){
	
	if(discard_.size() == 0)
		return nullptr;
	
	Card* card = discard_.back();
	discard_.pop_back();

	assert(card);
	return card;	
}

//gets the top card from deck
Card* Gameboard::DrawCardFromDeck(){
	//add animation//
	if(deck_.size() == 0)
		//game is over, do smth
		return nullptr;

	Card* card = deck_.back();
	deck_.pop_back();

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
void Gameboard::DiscardCard(Card* c){

	assert(c);
	discard_.push_back(c);
	c->sprite_.setPosition(discard_pos);
}


void Gameboard::Run(){

	Card* new_card = nullptr;

	while(!is_done_){

		if(game_area_.size() != 0){
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

		new_card = PutCardInGameArea();

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