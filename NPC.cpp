#include "NPC.h"
#include <iostream>
#include <string>
#include "parameters.h"

NPC::NPC() {}; // default constructor 

NPC::NPC(const NPC& s) : // copy constuctor, creates new NPC using an existing NPC
	_sprite(s._sprite) {} // initalises the new NPC with the same sprite 

NPC::NPC(std::string filepath) : Sprite() {
    if (!spriteSheet.loadFromFile(
        "Debug/res/" + filepath)) // THE PROJECT SHOULD NOT BE SUBMITTED IN DEBUG, ALL FILEPATHS MUST BE CHANGED BEFORE SUBMISSION 
    {
        std::cerr << "Failed to load "+ filepath << std::endl;
    }
	setTexture(spriteSheet);
	setTextureRect(_sprite);
};

int NPC::update(const float& dt) {
    animationTimer += dt;
    if (animationTimer >= Parameters::animationSpeed) {
        animationTimer -= Parameters::animationSpeed;
        currentFrame++;
        if (currentFrame >= 8 || currentFrame >= 4 && row == 4) {
            currentFrame = 0;
        }
    }

    setTextureRect(
        sf::IntRect(
            currentFrame * Parameters::FRAME_WIDTH,
            row * Parameters::FRAME_HEIGHT,
            Parameters::FRAME_WIDTH,
            Parameters::FRAME_HEIGHT
        )
    );
    return currentFrame;
}

NPC::~NPC() = default;