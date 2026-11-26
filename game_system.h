#pragma once
#include <SFML/Graphics.hpp>

struct GameSystems
{
	static void init();
	static void render(sf::RenderWindow& window);
	static void update(float dt);
};