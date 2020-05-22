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

Card* Gameboard::MermaidAbility(){
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
	return nullptr;
}

Card* Gameboard::KrakenAbility(){
	return nullptr;
}
