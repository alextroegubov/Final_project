#include "cards.h"
Card::Card(CardType t, int points, std::function<Card*(Card*)> ability):
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


bool Card::IsClicked(int x, int y){

	return  (pos_.x <= x) && (x <= pos_.x + size_.x) &&
			(pos_.y <= y) && (y <= pos_.y + size_.y);
}


bool Card::IsClicked(sf::Vector2i pos){

	return IsClicked(pos.x, pos.y);	
}