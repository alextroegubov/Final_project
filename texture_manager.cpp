#include "texture_manager.hpp"
#include <cassert>

void TextureManager::Load(int id, const std::string& filename){
	
	sf::Texture* new_texture = new sf::Texture();
	assert(new_texture);

	if(!new_texture->loadFromFile(filename))
		assert("can't load from file");
	
	textures_[id] = new_texture;
}


TextureManager::~TextureManager(){
	for(auto& item: textures_)
		delete item.second;
}


const sf::Texture& TextureManager::Get(int id) const{

	assert(textures_.at(id));

	return *(textures_.at(id));
}

void TextureManager::LoadAll(){
	
	std::map<Card::CardType, std::string> my_files =
	{
		{Card::CardType::Cannon, 		"images/Cannon.png"},
		{Card::CardType::Anchor, 		"images/Anchor.png"},
		{Card::CardType::Hook, 			"images/Hook.png"},
		{Card::CardType::Key, 			"images/Key.png"},
		{Card::CardType::Chest, 		"images/Chest.png"},
		{Card::CardType::Scroll, 		"images/Scroll.png"},
		{Card::CardType::CrystalBall, 	"images/CrystalBall.png"},
		{Card::CardType::Sabre, 		"images/Sabre.png"},
		{Card::CardType::Mermaid, 		"images/Mermaid.png"},
		{Card::CardType::Kraken, 		"images/Kraken.png"}
	};

	for(const auto& i: my_files){
		Load(i.first, i.second);
	}
	
	Load(Table, "images/Table.png");
	textures_.at(Table)->setRepeated(true);

	Load(Menu, "images/Sea.png");

	Load(Deck, "images/Deck.png");

	Load(ScrollAbility, "images/ScrollAbility.png");

	Load(Rule, "images/Rule.png");

	Load(RuleButton, "images/Rule_button.png");
}