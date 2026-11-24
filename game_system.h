#pragma once
#include <SFML/Graphics.hpp>

struct GameSystems
{
	static void init();
	static void render(sf::RenderWindow& window);
	static int update(float dt,int Currentframe);
	static sf::FloatRect getPlayerFeetBounds();
};