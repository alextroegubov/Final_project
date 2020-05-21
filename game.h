#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "player.h"
#include "texture_manager.hpp"
#include "ui.h"
/*
#define DX 20
#define DY 20
#define CARD_X 90
#define CARD_Y 140
#define BORDER 25
*/

class Gameboard{
public:
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
	//
	void TakeGameArea();

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


	std::vector<Card> card_holder_;

	Ui ui_;
	bool is_done_;
};