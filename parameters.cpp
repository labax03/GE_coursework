#pragma once //insure that this header file is included only once and there will no multiple definition of the same thing
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include "parameters.h"

    sf::Sprite Parameters::player;

    sf::Sprite Parameters::elf; // sprites will be held a class variable when we switch to object oriented 
    sf::Sprite Parameters::orc; // 
    sf::Sprite Parameters::knight; // 

    sf::Texture Parameters::davequaviousTexture;
    sf::Texture Parameters::orcTexture;
    sf::Texture Parameters::elfTexture;
    sf::Texture Parameters::knightTexture;

    // Background
    sf::Texture Parameters::backgroundTexture;
    sf::Sprite Parameters::backgroundSprite;

    // Foreground
    sf::Texture Parameters::foregroundTexture;
    sf::Sprite Parameters::foregroundSprite;



    tmx::Map Parameters::villageMap;
    std::vector<sf::FloatRect> Parameters::collisionRects;