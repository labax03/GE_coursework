#include <SFML/Graphics.hpp>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>
#include "Parameters.h"
#include "game_system.h"
#include "NPC.h"

/// <summary>/// /// </summary>

void GameSystems::init() {

    // Background
    Parameters::backgroundTexture.loadFromFile("Debug/res/Village_map/village_background.png");
    Parameters::foregroundTexture.loadFromFile("Debug/res/Village_map/village_foreground.png");

    // Background sprites
    Parameters::backgroundSprite.setTexture(Parameters::backgroundTexture);
    Parameters::foregroundSprite.setTexture(Parameters::foregroundTexture);

    // Positions
    Parameters::backgroundSprite.setPosition(0.f, 0.f);
    Parameters::foregroundSprite.setPosition(0.f, 0.f);

    // Optional: smoother scaling
    Parameters::davequaviousTexture.setSmooth(false);
    Parameters::orcTexture.setSmooth(false);

    // Create player sprite
    //Parameters::player.setTexture(Parameters::davequaviousTexture);


    // Centre origin so scaling looks better
    Parameters::player.setOrigin(
        Parameters::FRAME_WIDTH / 2.0f,
        Parameters::FRAME_HEIGHT / 2.0f
    );
}

void GameSystems::update(float dt) {

    Parameters::player.update(dt);
    Parameters::elf.update(dt);
    Parameters::orc.update(dt);
    Parameters::knight.update(dt);
}

void GameSystems::render(sf::RenderWindow& window)
{
    // Background
    window.draw(Parameters::backgroundSprite);

    // Player
    window.draw(Parameters::player);
    window.draw(Parameters::elf);
    window.draw(Parameters::orc);
    window.draw(Parameters::knight);


    // Foreground
    window.draw(Parameters::foregroundSprite);
    /*
    window.draw(fgTRSprite);
    window.draw(fgBLSprite);
    window.draw(fgBRSprite);
    */
}
int main()
{
    int row = 4; // row 4 contains the idle sprite animations 

    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "ScorchQuest"
    );

    std::cout << "Maximum texture size: "
        << sf::Texture::getMaximumSize()
        << std::endl;

    if (!Parameters::villageMap.load(
        "Debug/res/village_map/village_map.tmx"))
    {
        std::cout << "Map failed to load" << std::endl;
        return -1;
    }

    GameSystems::init();

    sf::View camera;
    camera.setSize(800.f, 600.f);
    camera.setCenter(Parameters::player.getPosition());

    // move player to PlayerSpawn object
    for (const auto& layer : Parameters::villageMap.getLayers())
    {
        if (layer->getName() == "spawns")
        {
            auto* objectLayer =
                dynamic_cast<tmx::ObjectGroup*>(layer.get());

            if (!objectLayer)
                continue;

            for (const auto& object : objectLayer->getObjects())
            {
                if (object.getName() == "PlayerSpawn")
                {
                    Parameters::player.setPosition(
                        object.getPosition().x,
                        object.getPosition().y
                    );
                }
                if (object.getName() == "KnightSpawn")
                {
                    Parameters::knight.setPosition(
                        object.getPosition().x,
                        object.getPosition().y
                    );
                }
                if (object.getName() == "FairySpawn")
                {
                    Parameters::elf.setPosition(
                        object.getPosition().x,
                        object.getPosition().y
                    );
                }
                if (object.getName() == "OrcSpawn")
                {
                    Parameters::orc.setPosition(
                        object.getPosition().x,
                        object.getPosition().y
                    );
                }
            }
        }
    }

    // load collision rectangles
    for (const auto& layer : Parameters::villageMap.getLayers())
    {
        if (layer->getName() == "collisions")
        {
            auto* objectLayer =
                dynamic_cast<tmx::ObjectGroup*>(layer.get());

            if (!objectLayer)
                continue;

            for (const auto& object : objectLayer->getObjects())
            {
                Parameters::collisionRects.emplace_back(
                    object.getPosition().x,
                    object.getPosition().y,
                    object.getAABB().width,
                    object.getAABB().height

                );
            }
        }
    }
    // map collision boundaries
    float mapWidth = Parameters::villageMap.getTileCount().x * Parameters::villageMap.getTileSize().x;
    float mapHeight = Parameters::villageMap.getTileCount().y * Parameters::villageMap.getTileSize().y;
    float thickness = 100.f; // thickness of the collision boundaries

    // Left boundary
    Parameters::collisionRects.emplace_back(-thickness, 0.f, thickness, mapHeight);

    // Right boundary
    Parameters::collisionRects.emplace_back(mapWidth, 0.f, thickness, mapHeight);

    // Top boundary
    Parameters::collisionRects.emplace_back(0.f, -thickness, mapWidth, thickness);

    // Bottom boundary
    Parameters::collisionRects.emplace_back(0.f, mapHeight, mapWidth, thickness);

    // Camera boundaries
    float halfWidth = camera.getSize().x / 2.f;
    float halfHeight = camera.getSize().y / 2.f;

    float minX = halfWidth;
    float maxX = mapWidth - halfWidth;

    float minY = halfHeight;
    float maxY = mapHeight - halfHeight;




    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        static sf::Clock clock;
        const float dt = clock.restart().asSeconds();

        GameSystems::update(dt);

        sf::Vector2f cameraPosition =
            Parameters::player.getPosition();

        cameraPosition.x =
            std::max(minX,
                std::min(maxX, cameraPosition.x));

        cameraPosition.y =
            std::max(minY,
                std::min(maxY, cameraPosition.y));

        camera.setCenter(cameraPosition);

        window.setView(camera);

        window.clear();

        GameSystems::render(window);

        window.display();

        sf::sleep(sf::seconds(Parameters::time_step));
    }

    return 0;
}