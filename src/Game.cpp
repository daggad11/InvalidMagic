#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "DebugText.hpp"
#include "Entity.hpp"
#include "World.hpp"
#include "HUD.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    sf::View view(sf::FloatRect(0, 0, window.getSize().x/2, window.getSize().y/2));

    sf::Clock timer;

    //used to show debug text on screen
    DebugText debug(3);
    int fps = 0; 

    //used to calculate fps
    double lastTime; 
    double currentTime;
    int totalFrames = 0;
    int frames = 0;
    lastTime = timer.getElapsedTime().asSeconds();

    //creating world
    World world(&timer);

    //getting pointer to player from world
    Player* player = world.getPlayer();

    //creating HUD
    HUD hud(player, &view, &window);

    //used for player movement
    bool moveRight;
    bool moveLeft;
    bool moveUp;
    bool moveDown;

    timer.restart();

    //main game loop
    while (window.isOpen())
    {   
        //handling user input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //player movement, checking state of movement keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
                moveRight = true;
            else
                moveRight = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
                moveLeft = true;
            else
                moveLeft = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
                moveUp = true;
            else
                moveUp = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
                moveDown = true;
            else
                moveDown = false;
            //setting all movement variables at once 
            player->setMoving(moveRight, moveLeft, moveUp, moveDown);

            //Player attacking directions
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
                player->setAttacking(Entity::Direction::LEFT, true);
            else
                player->setAttacking(Entity::Direction::LEFT, false);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                player->setAttacking(Entity::Direction::RIGHT, true);
            else
                player->setAttacking(Entity::Direction::RIGHT, false);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                player->setAttacking(Entity::Direction::UP, true);
            else
                player->setAttacking(Entity::Direction::UP, false);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                player->setAttacking(Entity::Direction::DOWN, true);
            else
                player->setAttacking(Entity::Direction::DOWN, false);
            
        }

        //updating everything in world
        world.update();
        //updating HUD
        hud.update();

        //centering view on player
        view.setCenter(((sf::Vector2f)(player->getPosition()*64)));
        window.setView(view);

        //moving debug text to line up with view
        debug.setPosition(sf::Vector2f(view.getCenter().x - window.getSize().x/4, view.getCenter().y - window.getSize().y/4));

        //clearing and drawing to window
        window.clear();
        window.draw(world);
        window.draw(debug);
        window.draw(hud);
        window.display();

        //calculating fps and showing debug text every 0.25 seconds
        currentTime = timer.getElapsedTime().asSeconds();
        if (currentTime - lastTime >= 0.25) {
            fps = frames * 4;
            lastTime = currentTime;
            frames = 0;

            //setting debug lines
            debug.setLine(0, "FPS: " + std::to_string(fps));
            debug.setLine(1, "Average FPS: " + std::to_string((int)(totalFrames / timer.getElapsedTime().asSeconds())));
            debug.setLine(2, "Player Health: " + std::to_string((int)player->getStats()[Player::StatName::HEALTH]));
        }
        frames++;
        totalFrames++;
    }

    return 0;
}