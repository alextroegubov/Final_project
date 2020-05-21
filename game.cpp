#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>

Gameboard::Gameboard():
	is_done_(false),
	act_pl_(0){

	Init();
}

void Gameboard::CreateCards(){

	std::vector<Card::CardType> types = {Card::Cannon, Card::Anchor, Card::Hook, Card::Key, Card::Chest, 
										 Card::Scroll, Card::CrystalBall, Card::Sabre, Card::Kraken, Card::Mermaid};

	for(int points = 2; points <= 7; points++){
		for(auto& t: types){
			card_holder_.push_back(Card(t, (t == Card::Mermaid) ? points + 2 : points, Abilities[t]));
		}		
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

	CreateCards();

}

Gameboard::~Gameboard(){
	Finish();
}

void Gameboard::Finish(){
	is_done_ = true;
	
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


void Gameboard::TakeGameArea(){

	auto b = game_area_.begin();
	auto e = game_area_.end();

	auto key = std::find_if(b, e, [](Card* c){return (c->type_ == Card::Key);});
	auto chest = std::find_if(b, e, [](Card* c){return (c->type_ == Card::Chest);});

	std::vector<Card*> to_take(game_area_);

	Card* taken_card = nullptr;

	if(key != e && chest != e){

		ShuffleDiscard();
		
		for(int i = 0; i < game_area_.size(); i++){

			taken_card = DrawCardFromDiscard();

			if(taken_card){
				to_take.push_back(taken_card);
				taken_card->is_active_ = true;
			}
			else 
				break;
		}
	}
	players_.at(act_pl_)->TakeCards(std::move(to_take));

	game_area_.clear();
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

	card->is_active_ = true;
	ui_.SetCardInGameArea(card, game_area_.size());

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
	c->is_active_ = false;
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

		ui_.GetWindow().pollEvent(event);
		
		switch(event.type){

			case sf::Event::Closed:
				Finish();
				break;
			case sf::Event::MouseButtonPressed:

				if(event.key.code == sf::Mouse::Left)
					new_card = PutCardInGameArea();
				else 
					TakeGameArea();
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				break;
		}

		Draw();
	}
}

//
void Gameboard::Draw(){

//	printf("deck_pos = (%f,%f)\n", deck_pos.x, deck_pos.y);
//	printf("window size = (%lu, %lu)\n", window_->getSize().x,
//										 window_->getSize().y);
	ui_.BeginPaint();
	assert(card_holder_.size() == 60);
	ui_.PaintTable();
	ui_.PaintCards(card_holder_);

	ui_.EndPaint();

}