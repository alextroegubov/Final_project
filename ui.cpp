#include "ui.h"
#include <cassert>
#include <thread>

Ui* Ui::ui_entity = nullptr;

Ui::~Ui(){

	window_->close();
	delete window_;
}

Ui::Ui():
		win_sz_({1300, 768}),
		is_done_(false){
		
		discard_pos_ = 	{(float)win_sz_.x - CARD_X - BORDER, 
						 (float)win_sz_.y / 2 - CARD_Y / 2};
		
		deck_pos_ = {discard_pos_.x - (CARD_X + DX),
					discard_pos_.y};

		CreateWindow();
		CreateSprites();

		ui_entity = this;

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

	printf("Sprites creation - ok!\n");
	fflush(stdout);

	table_sprite_.setTexture(t_manager_.Get(TextureManager::Table));
	table_sprite_.setTextureRect(sf::IntRect({0,0}, win_sz_));

	backside_.setTexture(t_manager_.Get(TextureManager::Backside));
	backside_.setTextureRect(sf::IntRect({0, 0}, size));
	backside_.scale((float)CARD_X / size.x, (float)CARD_Y / size.y);
}


void Ui::SetCardInGameArea(Card* card, int n){
	assert(card);
	assert(card->is_active_);

	Card::CardType t = card->type_;
	int pos = (t == Card::Mermaid) ? card->points_ - 4 : card->points_ - 2;

	assert(pos < 6);

	sprites_.at(t).at(pos).setPosition(	BORDER + (DX + CARD_X) * n,  //?? n - 1 
										win_sz_.y / 2 - CARD_Y / 2);
	card->pos_ = {BORDER + (DX + CARD_X) * n,  win_sz_.y / 2 - CARD_Y / 2};

	printf("game area - ok!\n");
}

void Ui::PaintCards(const std::vector<Card>& cards){
	assert(window_);

	Card::CardType t;
	int pos;

	for(const auto& card: cards){
		assert(cards.size() == 60);
			
		if(card.is_active_){

			t = card.type_;
			pos = (t == Card::Mermaid) ? card.points_ - 4 : card.points_ - 2;
			assert(pos < 6);
			window_->draw(sprites_.at(t).at(pos));
		}

	}
}

void Ui::PaintTable(){

	window_->draw(table_sprite_);

	backside_.setPosition(deck_pos_);
	window_->draw(backside_);

	backside_.setPosition(discard_pos_);
	window_->draw(backside_);
}

void Ui::BeginPaint(){

	window_->clear();
}

void Ui::EndPaint(){

	window_->display();
}

void Ui::SetCardForPlayer(int n, const std::vector<Card*>& cards){

	int v_offset = 0;
	sf::Vector2f pos = {50, 768 - 300};

	Card::CardType t;
	int p;

	for(const auto& c: cards){
		assert(c);
		t = c->type_;
		p = (t == Card::Mermaid) ? c->points_ - 4 : c->points_ - 2;

		assert(p < 6);
		sprites_.at(t).at(p).setPosition({pos.x + 120 * (t), pos.y + v_offset});
		c->pos_ = {pos.x + 120 * (t), pos.y + v_offset};

		v_offset += 20;
	}
}