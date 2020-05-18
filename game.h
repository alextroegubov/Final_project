#pragma once

#include <vector>

#include "cards.h"
#include "player.h"
#include "texture_manager.hpp"

class Gameboard{
public:
	const int width = 1366;
	const int height = 768;

	const sf::Vector2i basic_size = {90, 135};

	const sf::Vector2f deck_pos = 		{(float)width - basic_size.x - 80,  (float)height / 2};
	const sf::Vector2f discard_pos = 	{(float)width - 50, 				(float)height / 2}; 
 

	Gameboard();
	void Init();
	void StartGame();
	~Gameboard();

	void Shuffle(std::vector<Card*>);
	Card* DrawCard();
	void DiscardGameArea();
	void Finish();
	void Draw();


private:
	std::vector<Card*> discard_;
	std::vector<Card*> game_area_;
	std::vector<Card*> deck_;
	std::vector<Player*> players_;
	sf::RenderWindow* window_; //1366 * 1024

	sf::Sprite table_sprite_;

	TextureManager t_manager_;
	CardHolder c_manager_;

	bool is_done_;
};