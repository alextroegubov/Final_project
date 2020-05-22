#include "game.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <thread>
#include "player.h"
#include <iostream>
#include <cassert>

Card* Gameboard::AnchorAbility(){
	return nullptr;
}

Card* Gameboard::KeyAbility(){
	return nullptr;
}

Card* Gameboard::ChestAbility(){
	return nullptr;
}

Card* Gameboard::MermaidAbility(){
	return nullptr;
}

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
	return nullptr;
}

Card* Gameboard::CrystalBallAbility(){
	return nullptr;
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
