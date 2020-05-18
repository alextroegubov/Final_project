#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "player.h"
#include "texture_manager.hpp"

//#define width 1024
//#define height 720

class Gameboard{
public:
	const int width = 1300;
	const int height = 720;

	const sf::Vector2i basic_size = {90, 135};

	const sf::Vector2f deck_pos = 		{(float)width - basic_size.x - 80,  (float)height / 2};
	const sf::Vector2f discard_pos = 	{(float)width - 50, 				(float)height / 2}; 
 
	Gameboard(Gameboard&) = delete;
	Gameboard& operator=(Gameboard&) = delete;

	Gameboard();
	void Init();
	void StartGame();
	~Gameboard();

	void ShuffleDeck();
	Card* GetCardFromDeck();
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