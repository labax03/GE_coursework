#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "NPC.h"

class Player : public NPC {
public:
	Player();
	Player(const Player& s); // copy constructor 
	Player(std::string filepath); // constructor that takes a sprite
	virtual ~Player();
	virtual void update(const float& dt);
	sf::FloatRect getPlayerFeetBounds();
protected:
	sf::Vector2f oldPos = getPosition();
	
};