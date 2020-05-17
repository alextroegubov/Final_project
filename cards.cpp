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
void MermainAbility(){

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
	MermainAbility
};


Card::Card(CardType t, int points, sf::Sprite sprite, std::function<void(void)> ability):
		type_(t),
		points_(points),
		sprite_(sprite),
		ability_(ability),
		front_side_up_(false),
		is_active_(false)
		{	
}

