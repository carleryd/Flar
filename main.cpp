
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "World.h"
#include "Player.h"
#include "Controller.h"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "RPG Game");
    sf::RenderTexture rTexture;
    rTexture.create(200*40, 200*40);
    
    sf::View view(sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Vector2f(window.getSize().x, window.getSize().y));
//    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    view.setRotation(30);
    window.setView(view);
    window.setVerticalSyncEnabled(true);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    //sf::Text text("Hello SFML", font, 50);
    //text.setColor(sf::Color::Black);

    // Load a music to play
    /*sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }*/

    // Play the music
    //music.play();
    
    World* world = new World(window.getSize().x, window.getSize().y);
    Player* player = new Player(window.getSize().x, window.getSize().y);
    Controller* controller = new Controller();
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Check for key events
        controller->handleInput(player);
        
        // View
        if(player->getHasMoved()) {
            view.move(player->getMovedX(), player->getMovedY());
            window.setView(view);
        }
        
        // Clear screen
        window.clear();
        
        // Draw world
//        window.draw(world->draw(view));
//        window.draw(controller->draw());
        world->draw(rTexture, view);
        controller->draw(rTexture);
        
        rTexture.display();
        window.draw(sf::Sprite(rTexture.getTexture()));
        player->draw(window);
        player->setNotMoving();
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
