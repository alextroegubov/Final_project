#include "cards.h"

void CannonAbility(){

}
void AnchorAbility(){

}
void HookAbility(){

}
void KeyAbility(){

}
void ChestAbility(){

}
void ScrollAbility(){

}
void CrystalBallAbility(){

}
void SabreAbility(){

}
void MermaidAbility(){

}
void KrakenAbility(){

}

std::vector<std::function<void(void)>> Card::abilities = 
{
	CannonAbility,
	AnchorAbility,
	HookAbility,
	KeyAbility,
	ChestAbility,
	ScrollAbility,
	CrystalBallAbility,
	SabreAbility,
	KrakenAbility,
	MermaidAbility
};


Card::Card(CardType t, int points, sf::Sprite sprite, std::function<void(void)> ability):
		front_side_up_(false),
		type_(t),
		is_active_(false),
		points_(points),
		sprite_(sprite),
		ability_(ability){	
}


bool Card::operator<(const Card& c){

	if(type_ != c.type_)
		return type_ < c.type_;
	else
		return points_ < c.points_;
}

void Card::SetupSprite(){
	;
}