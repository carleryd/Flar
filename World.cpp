//
//  World.cpp
//  RPG-Game-SFML
//
//  Created by Christofer Ärleryd on 2013-11-23.
//  Copyright (c) 2013 Christofer Ärleryd. All rights reserved.
//

#include "World.h"
#include "ResourcePath.hpp"


World::World(int windowWidth, int windowHeight) {
    // How large the world is
    worldWidth = 200;
    worldHeight = 200;
    
    //Initiate all world objects(load only objects close to player)
    //std::string resourcePath() = "/Users/christoferarleryd/Programming/RPG-Game-SFML/RPG-Game-SFML/Resources/";
    //std::string resourcePath() = resourcePath()();
    
    sf::Image bitmap;
    bitmap.loadFromFile(resourcePath() + "world_bitmap.png");
    
    // Types of sprites
    grassTexture.loadFromFile(resourcePath() + "grass.png");
    sf::Sprite* grassSprite = new sf::Sprite(grassTexture);
    
    dirtTexture.loadFromFile(resourcePath() + "dirt.png");
    sf::Sprite* dirtSprite = new sf::Sprite(dirtTexture);
    
    worldTexture.create(200*40, 200*40);
    
    
    for(unsigned int x = 0; x < worldWidth; x++) {
        for(unsigned int y = 0; y < worldHeight; y++) {
            
            if(bitmap.getPixel(x, y) == sf::Color(0, 255, 0, 255)) { // Grass 00ff00
                sf::Sprite* temp = new sf::Sprite(*grassSprite);
                temp->move(x*40, y*40);
                worldSprites.push_back(new sf::Sprite(*temp));
            }
            else if(bitmap.getPixel(x, y) == sf::Color(99, 91, 3, 255)) { // Dirt 635b03
                sf::Sprite* temp = new sf::Sprite(*dirtSprite);
                temp->move(x*40, y*40);
                worldSprites.push_back(new sf::Sprite(*temp));
            }
        }
    }
}

void World::draw(sf::RenderTexture& rTexture, sf::View view) {
    // Draw images for world objects
    // Keep track of what we see and draw accordingly
    int extraPadding = 0;
    minViewX = view.getCenter().x - view.getSize().x/2 - extraPadding;
    maxViewX = view.getCenter().x + view.getSize().x/2 + extraPadding;
    minViewY = view.getCenter().y - view.getSize().y/2 - extraPadding;
    maxViewY = view.getCenter().y + view.getSize().y/2 + extraPadding;
    
    for(int i = 0; i < worldSprites.size(); i++) {
        if(worldSprites[i]->getPosition().x > minViewX && worldSprites[i]->getPosition().x < maxViewX &&
           worldSprites[i]->getPosition().y > minViewY && worldSprites[i]->getPosition().y < maxViewY) {
            rTexture.draw(*worldSprites[i]);
        }
    }
//    rTexture.display();
    
//    return sf::Sprite(worldTexture.getTexture());
}
