#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "cards.h"

class TextureManager{
public:
	enum Id{
		Table = 20,
		Deck,
		Backside,
		ScrollAbility,
		Menu,
		Rule,
		RuleButton
	};

	void LoadAll();

	sf::Texture& get(Card::CardType id);

	const sf::Texture& Get(int id) const;

	~TextureManager();

private:
	void Load(int id, const std::string& filename);

	std::map<int, sf::Texture*> textures_;
};