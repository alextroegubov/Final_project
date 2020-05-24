#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Card{
public:
	enum CardType{
		Cannon = 0,
		Anchor,
		Hook,
		Key,
		Chest,
		Scroll,
		CrystalBall,
		Sabre,
		Kraken,
		Mermaid
	};

	Card(CardType t, int points, std::function<Card*(Card*)> ability);

	void Draw();

	bool IsClicked(int x, int y);
	bool IsClicked(sf::Vector2i pos);

//	void Flip(){ front_side_up_ = !front_side_up_;}

	bool operator<(const Card&);

	void Update();

//protected:
//	bool front_side_up_; //front or back side up
	enum CardType type_;
	bool is_active_;
	int points_;
	bool highlight_;
	sf::Vector2i size_;
	sf::Vector2i pos_;
	std::function<Card*(Card*)> ability_;
};