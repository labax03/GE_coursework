#include <SFML/Graphics.hpp>
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

/*
fix foreground to line up / find easier way to render map
add barriers to outline of map
fix ratio for characters
*/

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

// Background
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

// Foreground
sf::Texture foregroundTexture;
sf::Sprite foregroundSprite;

int currentFrame = 0;
float animationTimer = 0.f;
int row = 4; // row 4 contains the idle sprite animations 

tmx::Map villageMap;
std::vector<sf::FloatRect> collisionRects;

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

    // Background
    backgroundTexture.loadFromFile("Debug/res/Village_map/village_background.png");
    foregroundTexture.loadFromFile("Debug/res/Village_map/village_foreground.png");

    // Background sprites
    backgroundSprite.setTexture(backgroundTexture);
    foregroundSprite.setTexture(foregroundTexture);

    // Positions
    backgroundSprite.setPosition(0.f, 0.f);
    foregroundSprite.setPosition(0.f, 0.f);
  
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
}
sf::FloatRect getPlayerFeetBounds()
{
    sf::FloatRect spriteBounds = player.getGlobalBounds();

    return sf::FloatRect(
        spriteBounds.left + 16.f,      // move inward
        spriteBounds.top + 52.f,       // near bottom
        32.f,                          // width
        12.f                           // height
    );
}

void update(float dt) {
    sf::Vector2f oldPos = player.getPosition();
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

    for (const auto& rect : collisionRects)
    {
        if (getPlayerFeetBounds().intersects(rect))
        {
            player.setPosition(oldPos);
            break;
        }
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

void render(sf::RenderWindow& window)
{
    // Background
    window.draw(backgroundSprite);

    // Player
    window.draw(player);

    
    // Foreground
    window.draw(foregroundSprite);
    /*
    window.draw(fgTRSprite);
    window.draw(fgBLSprite);
    window.draw(fgBRSprite);
    */
}
int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Character Selection"
    );

    std::cout << "Maximum texture size: "
        << sf::Texture::getMaximumSize()
        << std::endl;

    if (!villageMap.load(
        "Debug/res/village_map/village_map.tmx"))
    {
        std::cout << "Map failed to load" << std::endl;
        return -1;
    }

    init();

    sf::View camera;
    camera.setSize(800.f, 600.f);
    // original camera code 
   // camera.setCenter(player.getPosition());

    // move player to PlayerSpawn object
    for (const auto& layer : villageMap.getLayers())
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
                    player.setPosition(
                        object.getPosition().x,
                        object.getPosition().y
                    );
                }
            }
        }
    }

    // load collision rectangles
    for (const auto& layer : villageMap.getLayers())
    {
        if (layer->getName() == "collisions")
        {
            auto* objectLayer =
                dynamic_cast<tmx::ObjectGroup*>(layer.get());

            if (!objectLayer)
                continue;
  
            for (const auto& object : objectLayer->getObjects())
            {
                collisionRects.emplace_back(
                    object.getPosition().x,
                    object.getPosition().y,
                    object.getAABB().width,
                    object.getAABB().height
                );
            }
        }
    }

    // map collision boundaries
	float mapWidth = villageMap.getTileCount().x * villageMap.getTileSize().x;
	float mapHeight = villageMap.getTileCount().y * villageMap.getTileSize().y;
	float thickness = 100.f; // thickness of the collision boundaries

	// Left boundary
	collisionRects.emplace_back(-thickness, 0.f, thickness, mapHeight);

	// Right boundary
	collisionRects.emplace_back(mapWidth, 0.f, thickness, mapHeight);

	// Top boundary
	collisionRects.emplace_back(0.f, -thickness, mapWidth, thickness);

	// Bottom boundary
	collisionRects.emplace_back(0.f, mapHeight, mapWidth, thickness);

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

        update(dt);
        
		// original code for camera
        // camera.setCenter(player.getPosition());

		// Get player position for camera
		sf::Vector2f cameraPosition = player.getPosition();

		cameraPosition.x = std::max(minX, std::min(maxX, cameraPosition.x));
		cameraPosition.y = std::max(minY, std::min(maxY, cameraPosition.y));

        camera.setCenter(cameraPosition);
        window.setView(camera);

        window.clear();

        render(window);

        window.display();

        sf::sleep(sf::seconds(time_step));
    }

    return 0;
}