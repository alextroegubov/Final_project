#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Card{
public:
	void ApplyAbility(){ ability_();}
	void Draw();
	bool IsClicked(const sf::Vector2i& xy);
	bool IsClicked(int x, int y); 
	void SetPosition(int x, int y){ pos_ = {x, y};}
	void SetPosition(const sf::Vector2i& xy){ pos_ = xy;}

protected:
	bool is_active_;
	int points_;
	sf::Sprite sprite_;
	sf::Vector2i pos_;
	std::function<void(void)> ability_;
};

class CardHolder{
public:
	bool LoadCard(const std::string& filename);

private:
	std::vector<Card> cards_;
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