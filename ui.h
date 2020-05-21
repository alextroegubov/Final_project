#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "texture_manager.hpp"

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
	void BeginPaint();
	void EndPaint();


	void PainterDeck();
	sf::RenderWindow& GetWindow(){ return *window_;}
	void SetCardInGameArea(const Card* card, int n);
	void SetCardForPlayer(int n, const std::vector<Card*>&);

private:
	void CreateSprites();
	void CreateWindow();

private:
	sf::RenderWindow* window_;
	std::vector<std::vector<sf::Sprite>> sprites_;
	sf::Vector2i win_sz_;
	bool is_done_;

	sf::Sprite backside_;
	sf::Sprite table_sprite_;
	TextureManager t_manager_;

	sf::Vector2f discard_pos_;
	sf::Vector2f deck_pos_;
};
