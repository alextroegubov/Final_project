#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>
#include "player.h"
#include <iostream>
#include <cassert>

//does nothing
Card* Gameboard::AnchorAbility(){
	ui_.PlaySound(Card::Anchor);
	return nullptr;
}

//does nothing
Card* Gameboard::KeyAbility(){
	ui_.PlaySound(Card::Key);
	return nullptr;
}

//does nothing
Card* Gameboard::ChestAbility(){
	ui_.PlaySound(Card::Chest);
	return nullptr;
}

//does nothing
Card* Gameboard::MermaidAbility(){
	ui_.PlaySound(Card::Mermaid);
	return nullptr;
}

//ok
Card* Gameboard::CannonAbility(){

	Player* opnt = players_[(act_pl_ + 1) % 2];

	if(!opnt->HasCards())
		return nullptr;

	//waiting for clicking on opponent's card 
	sf::Event event;

	while(true){

		ui_.GetWindow().waitEvent(event);
		
		if(event.type == sf::Event::MouseButtonPressed){
			
			Card* c = opnt->GetCard(sf::Mouse::getPosition(ui_.GetWindow()));

			if(c != nullptr){
				ui_.PlaySound(Card::Cannon);
				DiscardCard(c);
				return nullptr;
			}
		}
	}
}

//ok
Card* Gameboard::HookAbility(){

	Player* me = players_[act_pl_];

	if(!me->HasCards())
		return nullptr;

	sf::Event event;

	while(true){

		ui_.GetWindow().waitEvent(event);

		if(event.type == sf::Event::MouseButtonPressed){
	
			Card* c = me->GetCard(sf::Mouse::getPosition(ui_.GetWindow()));
	
			if(c != nullptr){
				return PutCardInGameArea(c);
			}
		}
	}
}

//ok
Card* Gameboard::ScrollAbility(){

	std::vector<Card*> cards;
	Card* c = nullptr;

	ShuffleDiscard();

	while(cards.size() < 3 && !discard_.empty()){

		c = DrawCardFromDiscard();
		cards.push_back(c);
		c->is_active_ = true;
	}
	if(cards.empty())
		return nullptr;

	ui_.ScrollAbilityOn(cards);

	ui_.PlaySound(Card::Scroll);

	Draw();

	sf::Event event;

	while(true){

		ui_.GetWindow().waitEvent(event);

		if(event.type == sf::Event::MouseButtonPressed){

			for(auto& c: cards){
				
				if(c->IsClicked(sf::Mouse::getPosition(ui_.GetWindow()))){

					for(auto& cc: cards){
						if(c != cc)						
							DiscardCard(cc);
					}
					ui_.ScrollAbilityOff();

					return PutCardInGameArea(c);			
				}
			}
		}
	}
}

//ok
Card* Gameboard::CrystalBallAbility(){
	
	if(deck_.size() == 0)
		return nullptr;
	
	deck_.at(deck_.size() - 1)->is_active_ = true;
	ui_.PlaySound(Card::CrystalBall);
	
	Draw();

	sf::Event event;

	while(true){

		ui_.GetWindow().waitEvent(event);

		if(event.type == sf::Event::MouseButtonPressed){

			deck_.at(deck_.size() - 1)->is_active_ = false;
			return nullptr;
		}
	}
}

//ok
Card* Gameboard::SabreAbility(){

	Player* me = players_[act_pl_]; 
	Player* opnt = players_[(act_pl_ + 1) % 2];

	if(!opnt->HasCards())
		return nullptr;

	bool has_smth_to_choose = false;

	for(int i = 0; i < 10; i++){

		if(!opnt->GetCards().at(i).empty() && me->GetCards()[i].empty()){
			has_smth_to_choose = true;
		}
	}

	if(!has_smth_to_choose)
		return nullptr;

	sf::Event event;

	while(true){

		ui_.GetWindow().waitEvent(event);

		if(event.type == sf::Event::MouseButtonPressed){
	
			Card* c = opnt->GetCard(sf::Mouse::getPosition(ui_.GetWindow()));

			if(c && !me->HasType(c->type_)){
				ui_.PlaySound(Card::Sabre);
				return PutCardInGameArea(c);
			}
		}
	}
}

Card* Gameboard::KrakenAbility(){
	
	ui_.PlaySound(Card::Kraken);
	Card* c = PutCardInGameArea();
	//??empty deck?
	assert(c);
	static std::vector<Card::CardType> types = {Card::Scroll, Card::Hook, Card::Sabre};

	if(!(c->type_ == Card::Sabre || c->type_ == Card::Scroll || c->type_ == Card::Hook || c->type_ == Card::Kraken)){
		draw_card_this_step_ = true;
	}

	return c;
}
