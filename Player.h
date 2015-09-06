//
//  Player.h
//  RPG-Game-SFML
//
//  Created by Christofer Ärleryd on 2013-11-23.
//  Copyright (c) 2013 Christofer Ärleryd. All rights reserved.
//

#ifndef __RPG_Game_SFML__Player__
#define __RPG_Game_SFML__Player__

#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(int windowWidth, int windowHeight);
    
    void draw(sf::RenderWindow& window);
    
    float getPosX();
    float getPosY();
    float getMovedX();
    float getMovedY();
    int getWidth();
    int getHeight();
    bool getHasMoved();
    sf::Sprite* getSprite();
    
    void setPos(float x, float y);
    void setNotMoving();
    void setSprite(int startX, int startY, int width, int height);
    
private:
    sf::Texture texture;
    sf::Sprite* sprite;
    sf::Image tempImage;
    
    float posX, posY;
    float movedX, movedY;
    int width, height;
    bool hasMoved;
};

#endif /* defined(__RPG_Game_SFML__Player__) */
