#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Card{
public:
	static std::vector<std::function<void(void)>> abilities;

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

	enum Dir{
		Up,
		Right,
		Down,
		Left
	};

	Card(CardType t, int points, sf::Sprite sprite, std::function<void(void)> ability);

	void ApplyAbility(){ ability_();}

	void Draw();

	bool IsClicked(int x, int y); 
	//
	void SetupSprite();

	void Flip(){ front_side_up_ = !front_side_up_;}

	bool operator<(const Card&);

//protected:
	bool front_side_up_; //front or back side up
	enum CardType type_;
	bool is_active_;
	int points_;
	sf::Vector2i size_;
	sf::Vector2i pos_;
	Dir dir_;
	sf::Sprite sprite_;
	std::function<void(void)> ability_;
};

void CannonAbility();
void AnchorAbility();
void HookAbility();
void KeyAbility();
void ChestAbility();
void ScrollAbility();
void CrystalBallAbility();
void SabreAbility();
void MermaidAbility();
void KrakenAbility();

struct CardHolder{
	std::vector<Card> cards;
};
