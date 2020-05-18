#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "cards.h"

class TextureManager{
public:
	enum Id{
		Table = 20
	};

	void LoadAll();

//	sf::Texture& get(Card::CardType id);

	const sf::Texture& Get(int id) const;

private:
	void Load(int id, const std::string& filename);

	std::map<int, std::unique_ptr<sf::Texture>> textures_;
};