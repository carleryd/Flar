//
//  World.h
//  RPG-Game-SFML
//
//  Created by Christofer Ärleryd on 2013-11-23.
//  Copyright (c) 2013 Christofer Ärleryd. All rights reserved.
//

#ifndef __RPG_Game_SFML__World__
#define __RPG_Game_SFML__World__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"


class World
{
public:
    World(int windowWidth, int windowHeight);
    
    void draw(sf::RenderTexture& rTexture, sf::View view);
    
private:
    sf::Texture grassTexture, dirtTexture;
    sf::RenderTexture worldTexture;
    std::vector<sf::Sprite*> worldSprites;
    
    int worldWidth, worldHeight;
    int minViewX, maxViewX, minViewY, maxViewY;
    sf::View view;
};

#endif /* defined(__RPG_Game_SFML__World__) */
