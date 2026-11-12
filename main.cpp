#include <SFML/Graphics.hpp>
#include <iostream>

const int FRAME_WIDTH = 64;
const int FRAME_HEIGHT = 64;

const sf::Keyboard::Key controls[8] = {
    sf::Keyboard::W,   // Player UP
    sf::Keyboard::S,   // Player Down
    sf::Keyboard::A,  // Player Left
    sf::Keyboard::D, // Player Right
    sf::Keyboard::Num1,
    sf::Keyboard::Num2,
    sf::Keyboard::Num3,
    sf::Keyboard::Num4
};

sf::Sprite player;

const float time_step = 0.017f; //60 fps
const float animationSpeed = 0.12f;

sf::Texture davequaviousTexture;
sf::Texture orcTexture;
sf::Texture elfTexture;
sf::Texture knightTexture;

int currentFrame = 0;
float animationTimer = 0.f;
int row = 4; // row 4 contains the idle sprite animations 

/// <summary>/// /// </summary>

void init() {
    // Load Dave spritesheet
    if (!davequaviousTexture.loadFromFile(
        "Debug/res/davequavious.png")) // THE PROJECT SHOULD NOT BE SUBMITTED IN DEBUG, ALL FILEPATHS MUST BE CHANGED BEFORE SUBMISSION 
    {
        std::cerr << "Failed to load davequavious.png" << std::endl;
    }

    // Load Orc spritesheet
    if (!orcTexture.loadFromFile(
        "Debug/res/orc.png")) // THE PROJECT SHOULD NOT BE SUBMITTED IN DEBUG, ALL FILEPATHS MUST BE CHANGED BEFORE SUBMISSION 
    {
        std::cerr << "Failed to load orc.png" << std::endl;
    }

    // Load elf spritesheet
    if (!elfTexture.loadFromFile(
        "Debug/res/elf.png")) // THE PROJECT SHOULD NOT BE SUBMITTED IN DEBUG, ALL FILEPATHS MUST BE CHANGED BEFORE SUBMISSION 
    {
        std::cerr << "Failed to load elf.png" << std::endl;
    }

    // Load knight spritesheet
    if (!knightTexture.loadFromFile(
        "Debug/res/knight.png")) // THE PROJECT SHOULD NOT BE SUBMITTED IN DEBUG, ALL FILEPATHS MUST BE CHANGED BEFORE SUBMISSION 
    {
        std::cerr << "Failed to load knight.png" << std::endl;
    }

    // Optional: smoother scaling
    davequaviousTexture.setSmooth(false);
    orcTexture.setSmooth(false);

    // Create player sprite
    player.setTexture(davequaviousTexture);

    // Centre origin so scaling looks better
    player.setOrigin(
        FRAME_WIDTH / 2.0f,
        FRAME_HEIGHT / 2.0f
    );

    player.setPosition(400.f, 300.f);
}

void update(float dt) {
    row = 4; // reset animation to idle whne nothing is pressed
    

    if (sf::Keyboard::isKeyPressed(controls[0])) { // UP
        player.move(0.f, -3.f);
        row = 3;
        }
    if (sf::Keyboard::isKeyPressed(controls[1])) { // DOWN
            player.move(0.f, 3.f);
            row = 2;
        }

    if (sf::Keyboard::isKeyPressed(controls[2])) { // LEFT
            player.move(-3.f, 0.f);
            row = 0;
        }

    if (sf::Keyboard::isKeyPressed(controls[3])) { // RIGHT
            player.move(3.f, 0.f);
            row = 1;
        }
    if (sf::Keyboard::isKeyPressed(controls[4])) { // Dave
        player.setTexture(davequaviousTexture);
    }
    if (sf::Keyboard::isKeyPressed(controls[5])) { // orc
        player.setTexture(orcTexture);
    }
    if (sf::Keyboard::isKeyPressed(controls[6])) { // elf
        player.setTexture(elfTexture);
    }
    if (sf::Keyboard::isKeyPressed(controls[7])) { // knight
        player.setTexture(knightTexture);
    }
   
        animationTimer += dt;

        if (animationTimer >= animationSpeed){
            animationTimer = 0.f;
            currentFrame++;
            if (currentFrame >= 8 || currentFrame >= 4 && row == 4) {
                currentFrame = 0;
            }
        }



    player.setTextureRect(
        sf::IntRect(
            currentFrame * FRAME_WIDTH,
            row * FRAME_HEIGHT,
            FRAME_WIDTH,
            FRAME_HEIGHT
        )
    );
}

void render(sf::RenderWindow& window){
    window.draw(player);

}

int main() {
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Character Selection"
    );
    init();
    while (window.isOpen()) {
        static sf::Clock clock;
        const float dt = clock.restart().asSeconds();

        window.clear(sf::Color::Black);
        update(dt);
        render(window);
        sf::sleep(sf::seconds(time_step));
        window.display();
    }
}