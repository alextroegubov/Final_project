#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>
#include <iostream>


Gameboard::Gameboard():
	is_done_(false),
	act_pl_(0),
	draw_card_this_step_(false),
	taken_(false){

	Init();
}

void Gameboard::CreateCards(){

	std::vector<Card::CardType> types = {Card::Cannon, Card::Anchor, Card::Hook, Card::Key, Card::Chest, 
										 Card::Scroll, Card::CrystalBall, Card::Sabre, Card::Kraken, Card::Mermaid};

	for(int points = 2; points <= 7; points++){
		for(auto& t: types){
			card_holder_.push_back(Card(t, points, Abilities[t]));
		}		
	}

	assert(card_holder_.size() == 60);

	//puttng cards in the deck
	deck_.resize(card_holder_.size());

	for(size_t i = 0; i < deck_.size(); i++){
		deck_.at(i) = &(card_holder_.at(i));
		assert(deck_.at(i));
		deck_.at(i)->size_ = {CARD_X, CARD_Y};
	}
	assert(deck_.size() == 60);
}

void Gameboard::Init(){

	Abilities = 
{
	std::bind(&Gameboard::CannonAbility, this),
	std::bind(&Gameboard::AnchorAbility, this),
	std::bind(&Gameboard::HookAbility, this),
	std::bind(&Gameboard::KeyAbility, this),
	std::bind(&Gameboard::ChestAbility, this),
	std::bind(&Gameboard::ScrollAbility, this),
	std::bind(&Gameboard::CrystalBallAbility, this),
	std::bind(&Gameboard::SabreAbility, this),
	std::bind(&Gameboard::KrakenAbility, this),
	std::bind(&Gameboard::MermaidAbility, this)
};

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
	taken_ = true;
}

//
void Gameboard::DiscardGameArea(){
	
	for(auto& c: game_area_){
		assert(c);
		DiscardCard(c);
	}

	game_area_.clear();
	taken_ = true;
}


Card* Gameboard::PutCardInGameArea(Card* card){
	
	assert(card);

	card->is_active_ = true;
	ui_.SetCardInGameArea(card, game_area_.size());

	game_area_.push_back(card);

	return card;	
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


Card* Gameboard::ProcessCard(Card* card){
	assert(card);
	return Abilities[card->type_]();

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

		Draw();

		if(game_area_.size() != 0 && new_card != nullptr){
			assert(new_card);

			if(CheckGameArea(new_card)){
				new_card = ProcessCard(new_card);
//				Draw();
//				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				continue;
			}

		}

		//for kraken
		if(draw_card_this_step_){
			draw_card_this_step_ = false;
			new_card = PutCardInGameArea();
//			Draw();
			continue;
		}

		//change player
		if(taken_){
			act_pl_ = (act_pl_ + 1) % players_.size();
//			ui_.PaintActivePlayer(act_pl_);
			taken_ = false;
		}

		sf::Event event;

		while(ui_.GetWindow().pollEvent(event)){
		
			switch(event.type){

				case sf::Event::Closed:
					Finish();
					break;
				case sf::Event::MouseButtonPressed:

					if(event.key.code == sf::Mouse::Left)
						new_card = PutCardInGameArea();
					else{
						TakeGameArea();
						new_card = nullptr;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					break;
			}
		}

//		Draw();
	}
}

//
void Gameboard::Draw(){

	ui_.BeginPaint();
	assert(card_holder_.size() == 60);
	ui_.PaintTable();
	ui_.PaintDeck(deck_.size());
	ui_.PaintActivePlayer(act_pl_);
	ui_.PaintCards(card_holder_);

	ui_.EndPaint();

}