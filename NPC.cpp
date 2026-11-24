#include "NPC.h"

NPC::NPC() {}; // default constructor 

NPC::NPC(const NPC& s) : // copy constuctor, creates new NPC using an existing NPC
	_sprite(s._sprite) {} // initalises the new NPC with the same sprite 

NPC::NPC(sf::IntRect ir,sf::Texture spriteSheet) : Sprite() {
	_sprite = ir;
	setTexture(spriteSheet);
	setTextureRect(_sprite);
};

void NPC::update(const float& dt, const int& currentFrame) {}

NPC::~NPC() = default;