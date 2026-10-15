#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Character Selection"
    );

    window.setFramerateLimit(60);

    // Load Dave spritesheet
    sf::Texture davequaviousTexture;
    if (!davequaviousTexture.loadFromFile(
        "C:/Users/User/GE_coursework/resources/davequavious.png"))
    {
        std::cerr << "Failed to load davequavious.png" << std::endl;
        return -1;
    }

    // Load Orc spritesheet
    sf::Texture orcTexture;
    if (!orcTexture.loadFromFile(
        "C:/Users/User/GE_coursework/resources/unnamed_orc.png"))
    {
        std::cerr << "Failed to load unnamed_orc.png" << std::endl;
        return -1;
    }

    // Load elf spritesheet
    sf::Texture elfTexture;
    if (!elfTexture.loadFromFile(
        "C:/Users/User/GE_coursework/resources/elf.png"))
    {
        std::cerr << "Failed to load elf.png" << std::endl;
        return -1;
    }

    // Optional: smoother scaling
    davequaviousTexture.setSmooth(false);
    orcTexture.setSmooth(false);

    const int FRAME_WIDTH = 64;
    const int FRAME_HEIGHT = 64;

    // Create player sprite
    sf::Sprite player(davequaviousTexture);

    // Centre origin so scaling looks better
    player.setOrigin(
        FRAME_WIDTH / 2.0f,
        FRAME_HEIGHT / 2.0f
    );

    player.setPosition(400.f, 300.f);

    int currentFrame = 0;
    float animationTimer = 0.f;

    bool movingLeft = false;
    bool movingRight = false;
    bool movingForward = false;
    bool movingBackward = false;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                // Dave
                if (event.key.code == sf::Keyboard::Num1)
                {
                    player.setTexture(davequaviousTexture);
                    player.setScale(1.0f, 1.0f);
                    currentFrame = 0;

                    std::cout << "Dave selected" << std::endl;
                }

                // Orc
                if (event.key.code == sf::Keyboard::Num2)
                {
                    player.setTexture(orcTexture);

                    // Make orc bigger
                    player.setScale(1.5f, 1.5f);

                    currentFrame = 0;

                    std::cout << "Orc selected" << std::endl;
                }
                // elf
                if (event.key.code == sf::Keyboard::Num3)
                {
                    player.setTexture(elfTexture);

                    // Make orc bigger
                    player.setScale(1.5f, 1.5f);

                    currentFrame = 0;

                    std::cout << "elf selected" << std::endl;
                }
            }
        }

        // Movement Input
        movingLeft =
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

        movingRight =
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        movingForward =
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        movingBackward =
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

        // Movement
        if (movingLeft)
            player.move(-3.f, 0.f);

        if (movingRight)
            player.move(3.f, 0.f);

        if (movingForward)
            player.move(0.f, 3.f);

        if (movingBackward)
            player.move(0.f, -3.f);

        bool isMoving =
            movingLeft ||
            movingRight ||
            movingForward ||
            movingBackward;

        // Animation
        animationTimer += 0.1f;

        if (isMoving)
        {
            if (animationTimer >= 1.f)
            {
                animationTimer = 0.f;
                currentFrame = (currentFrame + 1) % 8;
            }
        }
        else
        {
            if (animationTimer >= 1.f)
            {
                animationTimer = 0.f;
                currentFrame = (currentFrame + 1) % 4;
            }
        }

        int row = 4;

        if (movingLeft)
            row = 0;
        else if (movingRight)
            row = 1;
        else if (movingForward)
            row = 2;
        else if (movingBackward)
            row = 3;

        player.setTextureRect(
            sf::IntRect(
                currentFrame * FRAME_WIDTH,
                row * FRAME_HEIGHT,
                FRAME_WIDTH,
                FRAME_HEIGHT
            )
        );

        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}