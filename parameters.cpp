#pragma once //insure that this header file is included only once and there will no multiple definition of the same thing
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include "parameters.h"

    Player Parameters::player("davequavious.png");
    //sf::Sprite Parameters::player;

    NPC Parameters::elf("elf.png"); 
    NPC Parameters::knight("knight.png");
    NPC Parameters::orc("orc.png");
    NPC Parameters::wizard("wizard.png");
    NPC Parameters::brandy("brandy.png");
    NPC Parameters::shlur("shlur.png");
    int Parameters::currentFrame = 0;

    sf::Texture Parameters::davequaviousTexture;
    sf::Texture Parameters::orcTexture;
    sf::Texture Parameters::elfTexture;
    sf::Texture Parameters::knightTexture;
    sf::Texture Parameters::wizardTexture;
    sf::Texture Parameters::brandyTexture;
    sf::Texture Parameters::shlurTexture;

    // Background
    sf::Texture Parameters::backgroundTexture;
    sf::Sprite Parameters::backgroundSprite;

    sf::Font Parameters::font;
    sf::Text Parameters::interactText;
    bool Parameters::showInteract = false;

    // Foreground
    sf::Texture Parameters::foregroundTexture;
    sf::Sprite Parameters::foregroundSprite;

    tmx::Map Parameters::villageMap;
    std::vector<sf::FloatRect> Parameters::collisionRects;
    std::vector<sf::FloatRect> Parameters::boundaryRects;

    sf::FloatRect Parameters::toForestRect;
    sf::FloatRect Parameters::toVillageRect;
    sf::FloatRect Parameters::toHouseRect;

    Parameters::MapType Parameters::currentMap =
    Parameters::MapType::Village;