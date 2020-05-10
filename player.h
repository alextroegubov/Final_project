#pragma once

#include <vector>

#include "cards.h"

class Player{
public:
	int CalculateScore();
	
private:
	std::vector<std::vector<Card*>> cards_;
};