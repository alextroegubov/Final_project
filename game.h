#pragma once

#include <vector>

#include "cards.h"
#include "player.h"
#include "texture_manager.hpp"

class Gameboard{
public:
	const int width = 1366;
	const int height = 720;

	Gameboard();
	void Init();

	void StartGame();
	void ShuffleDeck();
	void ShuffleDiscard();
	void DrawCard();
	void DiscardGameArea();
	void Finish();
	~Gameboard();

private:
	std::vector<Card*> discard_;
	std::vector<Card*> game_area_;
	std::vector<Card*> deck_;
	std::vector<Player*> players_;
	sf::RenderWindow* window_; //1280 * 1024
	
	TextureManager t_manager_;
	CardHolder c_manager_;

	bool is_done_;
};