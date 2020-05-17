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
		Mermain
	};

	Card(CardType t, int points, sf::Sprite sprite, std::function<void(void)> ability);

	void ApplyAbility(){ ability_();}
	void Draw();

	bool IsClicked(const sf::Vector2i& xy);
	bool IsClicked(int x, int y); 

	void SetPosition(int x, int y){ pos_ = {x, y};}
	void SetPosition(const sf::Vector2i& xy){ pos_ = xy;}

	void Flip(){ front_side_up_ = !front_side_up_;}

//protected:
	bool front_side_up_; //front or back side up
	enum CardType type_;
	bool is_active_;
	int points_;
	sf::Sprite sprite_;
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
void MermainAbility();
void KrakenAbility();

struct CardHolder{
	std::vector<Card> cards;
};

/*
class Cannon : public Card{
	void ApplyAbility();
};

class AnchorCard : public Card{
	void ApplyAbility();
};

class HookCard : public Card{
	void ApplyAbility();
};

class KeyCard : public Card{
	void ApplyAbility();
};

class ChestCard : public Card{
	void ApplyAbility();
};

class ScrollCard : public Card{
	void ApplyAbility();
};

class CrystalBallCard : public Card{
	void ApplyAbility();
};

class SabreCard : public Card{
	void ApplyAbility();
};

class MermaidCard : public Card{
	void ApplyAbility();
};

class Kraken : public Card{
	void ApplyAbility();
};
*/