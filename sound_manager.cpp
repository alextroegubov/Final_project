#include "sound_manager.hpp"
#include <cassert>


void SoundManager::Load(int id, const std::string& filename){
	
	sf::SoundBuffer* new_sound = new sf::SoundBuffer();
	assert(new_sound);

	if(!new_sound->loadFromFile(filename))
		assert("can't load from file");
	
	sounds_[id] = new_sound;
}


SoundManager::~SoundManager(){
	for(auto& item: sounds_)
		delete item.second;
}


const sf::SoundBuffer& SoundManager::Get(int id) const{

	assert(sounds_.at(id));

	return *(sounds_.at(id));
}

void SoundManager::LoadAll(){
	
	std::map<Card::CardType, std::string> my_files =
	{
		{Card::CardType::Cannon, 		"sound/Cannon.wav"},
		{Card::CardType::Anchor, 		"sound/Anchor.wav"},
		{Card::CardType::Hook, 			"sound/Hook.wav"},
		{Card::CardType::Key, 			"sound/Key.wav"},
		{Card::CardType::Chest, 		"sound/Chest.wav"},
		{Card::CardType::Scroll, 		"sound/Scroll.wav"},
		{Card::CardType::CrystalBall, 	"sound/CrystalBall.wav"},
		{Card::CardType::Sabre, 		"sound/Sabre.wav"},
		{Card::CardType::Mermaid, 		"sound/Mermaid.wav"},
		{Card::CardType::Kraken, 		"sound/Kraken.wav"}
	};

	for(const auto& i: my_files){
		Load(i.first, i.second);
	}
}