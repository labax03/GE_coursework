#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class NPC : public sf::Sprite {
	public:
		NPC(); 
		NPC(const NPC &s); // copy constructor 
		NPC(std::string filepath); // constructor that takes a sprite
		virtual ~NPC();
		virtual int update(const float& dt);
	protected:
		sf::IntRect _sprite;
		sf::Texture spriteSheet;
		int currentFrame = 0;
		int row = 4;
		float animationTimer = 0.f;


};

