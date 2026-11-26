#include "Player.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "parameters.h"

Player::Player() : NPC() {}; // default constructor 

Player::Player(const Player& s) : NPC(s) {} // copy constuctor,

Player::Player(std::string filepath) : NPC(filepath) {}

sf::FloatRect Player::getPlayerFeetBounds() {
    sf::FloatRect spriteBounds = Parameters::player.getGlobalBounds();

    return sf::FloatRect(
        spriteBounds.left + 16.f,      // move inward
        spriteBounds.top + 52.f,       // near bottom
        32.f,                          // width
        12.f                           // height
    );
}

void Player::update(const float& dt) {
    oldPos = Parameters::player.getPosition();
    row = 4;
    if (sf::Keyboard::isKeyPressed(Parameters::controls[0])) { // UP
        Parameters::player.move(0.f, -3.f);
        row = 3;
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[1])) { // DOWN
        Parameters::player.move(0.f, 3.f);
        row = 2;
    }

    if (sf::Keyboard::isKeyPressed(Parameters::controls[2])) { // LEFT
        Parameters::player.move(-3.f, 0.f);
        row = 0;
    }

    if (sf::Keyboard::isKeyPressed(Parameters::controls[3])) { // RIGHT
        Parameters::player.move(3.f, 0.f);
        row = 1;
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[4])) { // Dave
        Parameters::player.setTexture(Parameters::davequaviousTexture);
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[5])) { // orc
        Parameters::player.setTexture(Parameters::orcTexture);
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[6])) { // elf
        Parameters::player.setTexture(Parameters::elfTexture);
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[7])) { // knight
        Parameters::player.setTexture(Parameters::knightTexture);
    }

    for (const auto& rect : Parameters::collisionRects)
    {
        if (Player::getPlayerFeetBounds().intersects(rect))
        {
            Parameters::player.setPosition(oldPos);
            break;
        }
    }
    animationTimer += dt;

    if (animationTimer >= Parameters::animationSpeed) {
        animationTimer -= Parameters::animationSpeed;
        Parameters::currentFrame++;
        if (Parameters::currentFrame >= 8 || Parameters::currentFrame >= 4 && row == 4) {
            Parameters::currentFrame = 0;
        }
    }

    Parameters::player.setTextureRect(
        sf::IntRect(
            Parameters::currentFrame * Parameters::FRAME_WIDTH,
            row * Parameters::FRAME_HEIGHT,
            Parameters::FRAME_WIDTH,
            Parameters::FRAME_HEIGHT
        )
    );
}

Player::~Player() = default;