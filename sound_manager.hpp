#pragma once

#include <SFML/Audio.hpp>
#include "cards.h"

class SoundManager{
public:
	enum Music{
		MenuMusic,
		GameMusic
	};

	void LoadAll();

	const sf::SoundBuffer& Get(int id) const;
	void PlayMusic(int id);
	void StopMusic(int id);
	
	~SoundManager();

private:
	void LoadSound(int id, const std::string& filename);
	void LoadMusic(int id, const std::string& filename);

	std::map<int, sf::SoundBuffer*> sounds_;
	std::map<int, sf::Music*> music_;
};