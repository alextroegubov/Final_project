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
	return nullptr;
}

//does nothing
Card* Gameboard::KeyAbility(){
	return nullptr;
}

//does nothing
Card* Gameboard::ChestAbility(){
	return nullptr;
}

//does nothing
Card* Gameboard::MermaidAbility(){
	return nullptr;
}

//does nothing
Card* Gameboard::CannonAbility(){

	sf::Event event;
	std::cout << "processing Cannon\n";

	int pl = (act_pl_ + 1) % 2;

	if(!players_[pl]->HasCards())
		return nullptr;
	
	while(true){
		ui_.GetWindow().waitEvent(event);
		
		if(event.type == sf::Event::MouseButtonPressed){
			
			Card* c = players_[pl]->GetCard(sf::Mouse::getPosition(ui_.GetWindow()));
			if(c){
				DiscardCard(c);
				return nullptr;
			}
		}
		
	}
	return nullptr;
}


Card* Gameboard::HookAbility(){

	sf::Event event;
	std::cout << "processing Hook\n";

	if(!players_[act_pl_]->HasCards())
		return nullptr;

	while(true){

		ui_.GetWindow().waitEvent(event);

		//rewrite with &&
		if(event.type == sf::Event::MouseButtonPressed){
	
			Card* c = players_[act_pl_]->GetCard(sf::Mouse::getPosition(ui_.GetWindow()));
	
			if(c){
				return PutCardInGameArea(c);
			}
		}
	}
}


Card* Gameboard::ScrollAbility(){

	std::vector<Card*> cards;
	Card* c = nullptr;

	for(int i = 0; i < 3; i++){

		c = DrawCardFromDiscard();

		if(c != nullptr){
			cards.push_back(c);
			c->is_active_ = true;
		}
	}

	if(cards.empty())
		return nullptr;

	ui_.ScrollAbilityOn(cards);

	Draw();

	sf::Event event;

	while(true){

		ui_.GetWindow().waitEvent(event);
		//FIXME!!!!!!!!!
		if(event.type == sf::Event::MouseButtonPressed){
			for(auto& c: cards){
				
				if(c->IsClicked(sf::Mouse::getPosition(ui_.GetWindow()))){

					for(auto& cc: cards)
						DiscardCard(cc);

					ui_.ScrollAbilityOff();

					return PutCardInGameArea(c);			
				}
			}
		}
	}
	return nullptr;
}

Card* Gameboard::CrystalBallAbility(){
	
	sf::Event event;
	std::cout << "processing CrystallBall\n";

	if(deck_.size() == 0)
		return nullptr;
	
	deck_.at(deck_.size() - 1)->is_active_ = true;
	
	Draw();

	while(true){

		ui_.GetWindow().waitEvent(event);

		if(event.type == sf::Event::MouseButtonPressed){

			deck_.at(deck_.size() - 1)->is_active_ = false;
			return nullptr;
		}
	}
}

Card* Gameboard::SabreAbility(){
	
	sf::Event event;
	std::cout << "processing Sabre\n";

	Player* me = players_[act_pl_]; 
	Player* opnt = players_[(act_pl_ + 1) % 2];

	if(!opnt->HasCards())
		return nullptr;

	bool has_smth_to_choose = false;

	for(int i = 0; i < 10; i++){

		if(!opnt->GetCards().at(i).empty() && me->GetCards()[i].empty())
			has_smth_to_choose = true;
	}

	if(!has_smth_to_choose)
		return nullptr;

	while(true){

		ui_.GetWindow().waitEvent(event);

		//rewrite with &&
		if(event.type == sf::Event::MouseButtonPressed){
	
			Card* c = opnt->GetCard(sf::Mouse::getPosition(ui_.GetWindow()));

			if(c && !me->HasType(c->type_)){	
				return PutCardInGameArea(c);
			}
		}
	}

	return nullptr;
}

Card* Gameboard::KrakenAbility(){

	Card* c = PutCardInGameArea();
	assert(c);
	static std::vector<Card::CardType> types = {Card::Scroll, Card::Hook, Card::Sabre};

	if(!(c->type_ == Card::Sabre || c->type_ == Card::Scroll || c->type_ == Card::Hook)){
		draw_card_this_step_ = true;
	}

	return c;
}
