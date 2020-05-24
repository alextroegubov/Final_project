#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "cards.h"
#include "texture_manager.hpp"
#include "sound_manager.hpp"

const int DX  = 20;
const int DY  = 20;
const int CARD_X  = 90;
const int CARD_Y  = 140;
const int BORDER  = 25;

class Ui{
	static Ui* ui_entity;
public:
	static Ui* Get(){ return ui_entity;}

	Ui();
	Ui(Ui&) = delete;
	Ui& operator=(Ui& ) = delete;
	~Ui();

	void Start();
	void Finish();

	void PaintCards(const std::vector<Card>&);
	void PaintTable();
	void PaintActivePlayer(int n);
	void PaintDeck(int n);
	void PaintDiscard(int n);
	void BeginPaint();
	void EndPaint();


	void PainterDeck();
	void ScrollAbilityOn(std::vector<Card*>&);
	void ScrollAbilityOff();

	sf::RenderWindow& GetWindow(){ return *window_;}
	void SetCardInGameArea(Card* card, int n);
	void SetCardForPlayer(int n, const std::vector<Card*>&);
	void PlaySound(Card::CardType t);
	bool IsDeckClicked(sf::Vector2i ms_pos);

private:
	void CreateSprites();
	void CreateWindow();
	void CreateSounds();
	void LoadSounds();

private:
	sf::RenderWindow* window_;
	std::vector<std::vector<sf::Sprite>> sprites_;
	sf::Vector2i win_sz_;
	bool is_done_;
	bool scroll_on_;

	sf::Sprite deck_;
	sf::Sprite table_sprite_;
	sf::Sprite scroll_;
	TextureManager t_manager_;

	sf::Vector2f discard_pos_;
	sf::Vector2f deck_pos_;

	sf::Music music_;
	std::vector<sf::Sound> sounds_;
	SoundManager s_manager_;
};
