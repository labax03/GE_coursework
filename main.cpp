#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Basic Character Movement");
    window.setFramerateLimit(60);

    // Load spritesheet
    sf::Texture sheet;
    if (!sheet.loadFromFile("C:/Users/User/GE_coursework/resources/davequavious.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
        return -1;
    }

    // Player sprite
    sf::Sprite player(sheet);
    player.setPosition(400.f, 300.f);

    const int FRAME_WIDTH = 64;
    const int FRAME_HEIGHT = 64;

    int currentFrame = 0;
    float animationTimer = 0.f;

    bool movingLeft = false;
    bool movingRight = false;
    bool movingForward = false;
    bool movingBackward = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movement input
        movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

        movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        movingForward = sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        movingBackward = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

        // Update position
        if (movingLeft)
            player.move(-3.f, 0.f);
        if (movingRight)
            player.move(3.f, 0.f);
        if (movingForward)   
            player.move(0.f, 3.f);
        if (movingBackward)  
            player.move(0.f, -3.f);

        bool isMoving = movingLeft || movingRight || movingBackward || movingForward;

        animationTimer += 0.1f;

        if (isMoving) {
            if (animationTimer >= 1.f) {
                animationTimer = 0.f;
                currentFrame = (currentFrame + 1) % 8; 
            }
        }
        else {
            if (animationTimer >= 1.f) {
                animationTimer = 0.f;
                currentFrame = (currentFrame + 1) % 4; 
            }
        }

        // Row 0 = walking right
        // Row 1 = walking left
        int row = 4;
        if (movingLeft) row = 0;
        if (movingRight) row = 1;
        if (movingForward) row = 2;
        if (movingBackward) row = 3;

        player.setTextureRect(sf::IntRect(
            currentFrame * FRAME_WIDTH,
            row * FRAME_HEIGHT,
            FRAME_WIDTH,
            FRAME_HEIGHT
        ));

        window.clear(sf::Color::Black); 
        window.draw(player);
        window.display();
    }

    return 0;
}
