#include "texture_manager.hpp"
#include <cassert>

void TextureManager::Load(Card::CardType id, const std::string& filename){
	
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	if(!texture->loadFromFile(filename))
		assert("can't load from file");
	
	textures_[id] = std::move(texture);
}


const sf::Texture& TextureManager::Get(Card::CardType id) const{

	auto found = textures_.find(id);
	return *found->second;
}

void TextureManager::LoadAll(){
	
	std::map<Card::CardType, std::string> my_files =
	{
		{Card::CardType::Cannon, "Cannon.png"},
		{Card::CardType::Anchor, "Anchor.png"},
		{Card::CardType::Hook, "Hook.png"},
		{Card::CardType::Key, "Key.png"},
		{Card::CardType::Chest, "Chest.png"},
		{Card::CardType::Scroll, "Scroll.png"},
		{Card::CardType::CrystalBall, "CrystalBall.png"},
		{Card::CardType::Sabre, "Sabre.png"},
		{Card::CardType::Mermain, "Mermain.png"},
		{Card::CardType::Kraken, "Kraken.png"}
	};

	for(const auto& i: my_files){
		Load(i.first, i.second);
	}
	
}