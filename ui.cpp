#include "ui.h"
#include <cassert>
#include <thread>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <iostream>

Ui* Ui::ui_entity = nullptr;


Ui::~Ui(){

	window_->close();
	delete window_;
}


Ui::Ui():
		win_sz_({1300, 720}),
		is_done_(false),
		scroll_on_(false),
		rules_on_(false),
		rule_button_on_(false){
		
	discard_pos_ = 	{(float)win_sz_.x - CARD_X - BORDER, 
					 (float)win_sz_.y / 2 - CARD_Y / 2};
		
	deck_pos_ = {discard_pos_.x - (CARD_X + DX),
				discard_pos_.y};

	CreateWindow();
	CreateSprites();
	CreateSounds();

	ui_entity = this;
}


void Ui::Menu(){

	table_sprite_.setTexture(t_manager_.Get(TextureManager::Menu));
	table_sprite_.setTextureRect(sf::IntRect({0,0}, win_sz_));

	s_manager_.PlayMusic(SoundManager::MenuMusic);

	sf::Font font;

	if (!font.loadFromFile("images/arial.ttf")){
		assert("text");
	}

	sf::Text text;

	text.setString("Play game");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);

	text.setPosition({win_sz_.x / 2 - sizeof("Play game") * 100 / 4 , win_sz_.y / 2 - 50});
	
	BeginPaint();
	PaintTable();
	window_->draw(text);
	EndPaint();
}


void Ui::Start(){

	s_manager_.StopMusic(SoundManager::MenuMusic);
	s_manager_.PlayMusic(SoundManager::GameMusic);

	table_sprite_.setTexture(t_manager_.Get(TextureManager::Table));
	table_sprite_.setTextureRect(sf::IntRect({0,0}, win_sz_));
	rule_button_on_ = true;
}


void Ui::Finish(int pl_score_0, int pl_score_1){


}


bool Ui::IsDeckClicked(sf::Vector2i ms_pos){

	return 	(deck_pos_.x <= ms_pos.x) && (ms_pos.x <= deck_pos_.x + CARD_X + DX) &&
			((deck_pos_.y) <= ms_pos.y) && (ms_pos.y <= deck_pos_.y + CARD_Y + DY);
}


bool Ui::IsPlayPressed(sf::Vector2i ms_pos){
	
	return 	(win_sz_.x / 2 - sizeof("Play game") * 100 / 4 <= ms_pos.x) &&
			(ms_pos.x <= win_sz_.x / 2 + sizeof("Play game") * 100 / 4) &&
			(win_sz_.y / 2 - 50 <= ms_pos.y) && (ms_pos.y <= win_sz_.y / 2 + 50);
}

bool Ui::IsRuleClicked(sf::Vector2i ms_pos){

	return (win_sz_.x - 100 <= ms_pos.x) && (win_sz_.y - 100 <= ms_pos.y);
}

void Ui::PlaySound(Card::CardType t){

	sounds_.at(t).play();

}

void Ui::CreateSounds(){

	s_manager_.LoadAll();

	std::vector<Card::CardType> types = {Card::Cannon, Card::Anchor, Card::Hook, Card::Key, Card::Chest, 
										 Card::Scroll, Card::CrystalBall, Card::Sabre, Card::Kraken, Card::Mermaid};
	sounds_.resize(10);

	for(auto& t: types){
		sounds_.at(t).setBuffer(s_manager_.Get(t));	
	}

	sounds_.at(Card::Mermaid).setVolume(50.f);
}


void Ui::CreateWindow(){

	window_ = new sf::RenderWindow(sf::VideoMode(win_sz_.x, win_sz_.y), "Dead Man's Draw", sf::Style::Default);
	assert(window_);
}


void Ui::CreateSprites(){

	t_manager_.LoadAll();

	std::vector<Card::CardType> types = {Card::Cannon, Card::Anchor, Card::Hook, Card::Key, Card::Chest, 
										 Card::Scroll, Card::CrystalBall, Card::Sabre, Card::Kraken, Card::Mermaid};
	sprites_.resize(10);

	for(auto& v: sprites_)
		v.resize(6);

	sf::Vector2i size = {737, 1020};
	sf::Vector2i pos_in_tex;

	for(int p = 0; p < 6; p++){

		pos_in_tex = {p * size.x, 0};

		for(auto& t: types){

			sprites_.at(t).at(p) = sf::Sprite(t_manager_.Get(t));
			sf::Sprite& spr = sprites_.at(t).at(p);

			spr.setTextureRect(sf::IntRect(pos_in_tex, size)); ///////<<<<---------
			spr.scale((float)CARD_X / size.x, (float)CARD_Y / size.y);
			spr.setPosition(deck_pos_);
		}
	}

	deck_.setTexture(t_manager_.Get(TextureManager::Deck));
	deck_.scale((float)CARD_X / 529.0f * 1.2, (float)CARD_Y / 709.0f * 1.2);

	scroll_.setTexture(t_manager_.Get(TextureManager::ScrollAbility));
	scroll_.setTextureRect(sf::IntRect({0, 0}, {512, 383}));

	//512x383 - size of ScrollAbility texture
	scroll_.scale((3 * CARD_X + 3 * DX) / 512.0f, (CARD_Y + 2 * DY) / 383.0f);
	scroll_.setPosition({deck_pos_.x - 3 * CARD_X - 3 * DX, deck_pos_.y});

	rule_.setTexture(t_manager_.Get(TextureManager::Rule));
	rule_.setOrigin(1428 / 2, 1022 / 2);
	rule_.setScale(0.5, 0.5);
	rule_.setPosition({win_sz_.x / 2, win_sz_.y / 2});

	rule_button_.setTexture(t_manager_.Get(TextureManager::RuleButton));
	rule_button_.setPosition({win_sz_.x - 100, win_sz_.y - 100});
	//size 850x657
	rule_button_.setScale(100.f / 850, 100.f / 675);
}


void Ui::SetCardInGameArea(Card* card, int n){
	assert(card);
	assert(card->is_active_);

	Card::CardType t = card->type_;
	int pos = card->points_ - 2;

	assert(pos < 6);

	sprites_.at(t).at(pos).setPosition(BORDER + (DX + CARD_X) * n, win_sz_.y / 2 - CARD_Y / 2);

	card->pos_ = {BORDER + (DX + CARD_X) * n,  win_sz_.y / 2 - CARD_Y / 2};
}


void Ui::PaintCards(const std::vector<Card>& cards){
	assert(window_);

	Card::CardType t;
	int pos;

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Red);
	rect.setSize({CARD_X + 10, CARD_Y + 10});

	for(const auto& card: cards){
		assert(cards.size() == 60);
			
		if(card.is_active_){

			t = card.type_;
			pos = card.points_ - 2;
			assert(pos < 6);

			if(card.highlight_){
				rect.setPosition({card.pos_.x - 5, card.pos_.y - 5});
				window_->draw(rect);
			}

			window_->draw(sprites_.at(t).at(pos));
		}
	}

	if(rules_on_)
		window_->draw(rule_);
}


void Ui::PaintActivePlayer(int n){

	static sf::CircleShape marker(10.0f);

	marker.setFillColor(sf::Color::Red);

	sf::Vector2f pos;

	if(n == 1)
		pos = {BORDER, CARD_Y / 2};
	else if(n == 0)
		pos = {BORDER, win_sz_.y - CARD_Y};
	else
		assert(n == 0 || n == 1);

	marker.setPosition(pos);

	window_->draw(marker);
}


void Ui::PaintDeck(int n){

	if(n == 0)
		return;

	sf::Vector2i pos_in_tex = {(n > 5)? 4 * 529 : (n - 1) * 529, 0};
	//529x709 - size of one sprite in Deck.png
	deck_.setTextureRect(sf::IntRect(pos_in_tex, {529, 709}));
	deck_.setPosition(deck_pos_);
	window_->draw(deck_);
}


void Ui::PaintDiscard(int n){
	
	if(n == 0)
		return;

	sf::Vector2i pos_in_tex = {(n > 5)? 4 * 529 : (n - 1) * 529, 0};
	//529x709 - size of one sprite in Deck.png
	deck_.setTextureRect(sf::IntRect(pos_in_tex, {529, 709}));
	deck_.setPosition(discard_pos_);
	window_->draw(deck_);
}


void Ui::PaintTable(){

	window_->draw(table_sprite_);

	if(scroll_on_){
		window_->draw(scroll_);
	}

	if(rule_button_on_){
		window_->draw(rule_button_);
	}
}


void Ui::ScrollAbilityOff(){
	scroll_on_ = false;
}


void Ui::ScrollAbilityOn(std::vector<Card*>& cards){

	static sf::Vector2i size = {3 * CARD_X + 3 * DX, CARD_Y + DY / 2};
	static sf::Vector2f pos = {deck_pos_.x - size.x, deck_pos_.y};

	Card::CardType t;
	int p;

	int count = 0;

	for(auto& c: cards){
		assert(c);
		t = c->type_;
		p = c->points_ - 2;
		sprites_.at(t).at(p).setPosition({pos.x + DX + (CARD_X + DX / 4) * count, pos.y + DY});
		c->pos_ = {pos.x + DX + (CARD_X + DX / 4) * count, pos.y + DY};
		count++;
	}

	scroll_on_ = true;
}


void Ui::BeginPaint(){

	window_->clear();
}


void Ui::EndPaint(){

	window_->display();
}


void Ui::SetCardForPlayer(int n, const std::vector<Card*>& cards){
	assert(n == 0 || n == 1);

	int v_offset = 0;

	sf::Vector2f pos;

	if(n == 0)
		pos = {2 * BORDER, 768 - 2 * CARD_Y };
	else
		pos = {2 * BORDER, BORDER};

	Card::CardType t;
	int p;

	for(const auto& c: cards){
		assert(c);
		t = c->type_;
		p = c->points_ - 2;

		assert(p < 6);
		//FIX: 120 = card size.x + dx
		sprites_.at(t).at(p).setPosition({pos.x + 120 * t, pos.y + v_offset});
		c->pos_ = {pos.x + 120 * t, pos.y + v_offset};

		v_offset += 20;
	}
}