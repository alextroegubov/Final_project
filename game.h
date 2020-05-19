#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "player.h"
#include "texture_manager.hpp"
/*
#define DX 20
#define DY 20
#define CARD_X 90
#define CARD_Y 140
#define BORDER 25
*/
const int DX  = 20;
const int DY  = 20;
const int CARD_X  = 90;
const int CARD_Y  = 140;
const int BORDER  = 25;


class Gameboard{
public:

	sf::Vector2i GetWinSz(){ return win_sz_;}

//	const sf::Vector2i basic_size = {90, 135};

	sf::Vector2f deck_pos;
	sf::Vector2f discard_pos;

	Gameboard(Gameboard&) = delete;
	Gameboard& operator=(Gameboard&) = delete;

	Gameboard();

	void StartGame();
	~Gameboard();

	//
	Card* DrawCard();

	//
	void ShuffleDeck();
	//
	void ShuffleDiscard();
	//
	void DiscardGameArea();

	std::vector<Card*> GetGameArea();

	bool CheckGameArea(Card* card);

	void Run();

	void Finish();
	void Draw();

private:
	void ProcessCard(Card* card);

	void Init();
	//
	void CreateWindow();
	//FIXME: add specific sizes of sprites !?!?!?!?
	void CreateCards();

private:
	std::vector<Card*> discard_;
	std::vector<Card*> game_area_;
	std::vector<Card*> deck_;

	std::vector<Player*> players_;

	sf::RenderWindow* window_; //1366 * 1024
	sf::Sprite table_sprite_;
	TextureManager t_manager_;
	std::vector<Card> card_holder_;

	bool is_done_;
	sf::Vector2i win_sz_;
};