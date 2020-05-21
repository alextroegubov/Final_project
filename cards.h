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

	Card(CardType t, int points, std::function<void(void)> ability);

	void ApplyAbility(){ ability_();}

	void Draw();

	bool IsClicked(int x, int y); 

	void Flip(){ front_side_up_ = !front_side_up_;}

	bool operator<(const Card&);

	void Update();

//protected:
	bool front_side_up_; //front or back side up
	enum CardType type_;
	bool is_active_;
	int points_;
	sf::Vector2i size_;
	sf::Vector2i pos_;
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