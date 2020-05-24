#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>
#include <iostream>
#include <functional>


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

	using namespace std::placeholders;

	Abilities = 
{
	std::bind(&Gameboard::CannonAbility, this, _1),
	std::bind(&Gameboard::AnchorAbility, this, _1),
	std::bind(&Gameboard::HookAbility, this, _1),
	std::bind(&Gameboard::KeyAbility, this, _1),
	std::bind(&Gameboard::ChestAbility, this, _1),
	std::bind(&Gameboard::ScrollAbility, this, _1),
	std::bind(&Gameboard::CrystalBallAbility, this, _1),
	std::bind(&Gameboard::SabreAbility, this, _1),
	std::bind(&Gameboard::KrakenAbility, this, _1),
	std::bind(&Gameboard::MermaidAbility, this, _1)
};

	CreateCards();
}

Gameboard::~Gameboard(){
	Exit();
}

void Gameboard::Exit(){
	is_done_ = true;	
}


void Gameboard::Finish(){

//	ui_.DrawFinish();

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
	if(!card){
//		CalculateScore();
		is_done_ = true;
	}

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

	static std::vector<Card::CardType> cards = {
		Card::Cannon,
		Card::Sabre,
		Card::Hook,
		Card::CrystalBall,
		Card::Scroll
	};

	if(std::find(cards.begin(), cards.end(), card->type_) != cards.end())
		card->highlight_ = true;

	Draw();

	return Abilities[card->type_](card);
}

//
void Gameboard::DiscardCard(Card* c){

	assert(c);
	discard_.push_back(c);
	c->is_active_ = false;
}


void Gameboard::Run(){

	ui_.Menu();
	//processing menu
	while(true){

		sf::Event event;
		ui_.GetWindow().waitEvent(event);
		
		if((event.type == sf::Event::MouseButtonPressed) && 
			ui_.IsPlayPressed(sf::Mouse::getPosition(ui_.GetWindow())))
			break;
	}

	ui_.Start();

	Card* new_card = nullptr;

	while(!is_done_){

		Draw();
		if(game_area_.size() != 0 && new_card != nullptr){
			assert(new_card);

			if(CheckGameArea(new_card)){
				new_card = ProcessCard(new_card);
				continue;
			}
		}
		//for kraken
		if(draw_card_this_step_){

			draw_card_this_step_ = false;
			new_card = PutCardInGameArea();
			continue;
		}

		//change player
		if(taken_){
			act_pl_ = (act_pl_ + 1) % players_.size();
			taken_ = false;
		}

		sf::Event event;

		while(ui_.GetWindow().pollEvent(event)){
		
			switch(event.type){

				case sf::Event::Closed:
					Exit();
					break;
				case sf::Event::MouseButtonPressed:
					
					if(ui_.IsDeckClicked(sf::Mouse::getPosition(ui_.GetWindow()))){

						if(event.key.code == sf::Mouse::Left)
							new_card = PutCardInGameArea();
						else{
							TakeGameArea();
							new_card = nullptr;
						}
					}

					if(ui_.IsRuleClicked(sf::Mouse::getPosition(ui_.GetWindow()))){
						
						ui_.SetRule(true);
						Draw();

						while(true){
							ui_.GetWindow().waitEvent(event);

							if(event.type == sf::Event::MouseButtonPressed){
								ui_.SetRule(false);
								break;
							}
						}
					}
					break;
			}
		}
	}
}

//
void Gameboard::Draw(){

	ui_.BeginPaint();
	assert(card_holder_.size() == 60);
	ui_.PaintTable();
	ui_.PaintDeck(deck_.size());
	ui_.PaintDiscard(discard_.size());
	ui_.PaintActivePlayer(act_pl_);
	ui_.PaintCards(card_holder_);

	ui_.EndPaint();
}