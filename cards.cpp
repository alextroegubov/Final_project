#include "cards.h"

void CannonAbility(){

}
void AnchorAbility(){
	return;
}
void HookAbility(){

}
void KeyAbility(){
	return;
}
void ChestAbility(){
	return;
}
void ScrollAbility(){

}
void CrystalBallAbility(){

}
void SabreAbility(){

}
void MermaidAbility(){
	return;
}
void KrakenAbility(){

}

Card::Card(CardType t, int points, std::function<void(void)> ability):
//		front_side_up_(false),
		type_(t),
		is_active_(false),
		points_(points),
		ability_(ability){	
}


bool Card::operator<(const Card& c){

	if(type_ != c.type_)
		return type_ < c.type_;
	else
		return points_ < c.points_;
}
