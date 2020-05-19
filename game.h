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
	sf::Vector2f deck_pos;
	sf::Vector2f discard_pos;

	Gameboard(Gameboard&) = delete;
	Gameboard& operator=(Gameboard&) = delete;

	Gameboard();

	void StartGame();
	~Gameboard();

	//
	Card* DrawCardFromDeck();
	//
	Card* DrawCardFromDiscard();

	Card* PutCardInGameArea();
	//
	void ShuffleDeck();
	//
	void ShuffleDiscard();
	//
	void DiscardCard(Card*);
	//
	void DiscardGameArea();

	std::vector<Card*> GetGameArea();

	void AddPlayer(Player* p);

	void Run();

	void Finish();
	//change to paint
	void Draw();

private:
	void ProcessCard(Card* card);
	bool CheckGameArea(Card* card);

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
	int act_pl_; // = 0;

	sf::RenderWindow* window_; //1366 * 1024
	sf::Sprite table_sprite_;
	TextureManager t_manager_;
	std::vector<Card> card_holder_;

	bool is_done_;
	sf::Vector2i win_sz_;
};