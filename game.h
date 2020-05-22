#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "player.h"
#include "texture_manager.hpp"
#include "ui.h"

class Gameboard{
public:

	std::vector<std::function<Card*(void)>> Abilities;

	Gameboard(Gameboard&) = delete;
	Gameboard& operator=(Gameboard&) = delete;

	Gameboard();

	void StartGame();
	~Gameboard();

	//
	Card* DrawCardFromDeck();
	//
	Card* DrawCardFromDiscard();
	//
	void TakeGameArea();
	//
	Card* PutCardInGameArea();
	//
	Card* PutCardInGameArea(Card* card);
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
	Card* ProcessCard(Card* card);
	bool CheckGameArea(Card* card);

	void Init();
	//
	void CreateWindow();
	//FIXME: add specific sizes of sprites !?!?!?!?
	void CreateCards();

	Card* CannonAbility();
	Card* AnchorAbility();
	Card* HookAbility();
	Card* KeyAbility();
	Card* ChestAbility();
	Card* ScrollAbility();
	Card* CrystalBallAbility();
	Card* SabreAbility();
	Card* MermaidAbility();
	Card* KrakenAbility();

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