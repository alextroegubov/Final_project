#include "texture_manager.hpp"
#include <cassert>

void TextureManager::Load(int id, const std::string& filename){
	
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	if(!texture->loadFromFile(filename))
		assert("can't load from file");
	
	textures_[id] = std::move(texture);
}


const sf::Texture& TextureManager::Get(int id) const{

	auto found = textures_.find(id);
	return *found->second;
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
		{Card::CardType::Mermain, 		"images/Mermain.png"},
		{Card::CardType::Kraken, 		"images/Kraken.png"}
	};

	for(const auto& i: my_files){
		Load(i.first, i.second);
	}
	
	Load(Table, "images/Table.png");
	textures_[Table]->setRepeated(true);
}