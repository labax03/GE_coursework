#pragma once //insure that this header file is included only once and there will no multiple definition of the same thing
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include "NPC.h"
#include "player.h"

struct Parameters {
	static constexpr int FRAME_WIDTH = 64;
    static constexpr int FRAME_HEIGHT = 64;

    static constexpr sf::Keyboard::Key controls[8] = {
        sf::Keyboard::W,   // Player UP
        sf::Keyboard::S,   // Player Down
        sf::Keyboard::A,  // Player Left
        sf::Keyboard::D, // Player Right
        sf::Keyboard::Num1,
        sf::Keyboard::Num2,
        sf::Keyboard::Num3,
        sf::Keyboard::Num4
    };

    static Player player;

    static NPC elf; // sprites will be held a class variable when we switch to object oriented 
    static NPC orc; // 
    static NPC knight; // 

    static constexpr float time_step = 0.017f; //60 fps
    static constexpr float animationSpeed = 0.12f;
    static int currentFrame;

    static sf::Texture davequaviousTexture;
    static sf::Texture orcTexture;
    static sf::Texture elfTexture;
    static sf::Texture knightTexture;

    // Background
    static sf::Texture backgroundTexture;
    static sf::Sprite backgroundSprite;

    // Foreground
    static sf::Texture foregroundTexture;
    static sf::Sprite foregroundSprite; 

    static tmx::Map villageMap;
    static std::vector<sf::FloatRect> collisionRects;
};