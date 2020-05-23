#pragma once

#include <SFML/Audio.hpp>
#include "cards.h"

class SoundManager{
public:
	void LoadAll();

	const sf::SoundBuffer& Get(int id) const;

	~SoundManager();

private:
	void Load(int id, const std::string& filename);

	std::map<int, sf::SoundBuffer*> sounds_;
};