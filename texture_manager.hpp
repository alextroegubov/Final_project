#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "cards.h"

class TextureManager{
public:

	void LoadAll();

//	sf::Texture& get(Card::CardType id);

	const sf::Texture& Get(Card::CardType id) const;

private:
	void Load(Card::CardType id, const std::string& filename);

	std::map<Card::CardType, std::unique_ptr<sf::Texture>> textures_;
};