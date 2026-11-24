#pragma once
#include <SFML/Graphics.hpp>

class NPC : public sf::Sprite {
	public:
		NPC(); 
		NPC(const NPC &s); // copy constructor 
		NPC(sf::IntRect ir, sf::Texture spriteSheet); // constructor that takes a sprite
		virtual ~NPC() = 0;
		virtual void update(const float& dt, const int& currentFrame);
	protected:
		sf::IntRect _sprite;

};

