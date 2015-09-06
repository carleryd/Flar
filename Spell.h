#ifndef __RPG_Game_SFML__Spell__
#define __RPG_Game_SFML__Spell__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Math.h"

using namespace std;

enum Direction {
    Down, Up, Left, Right, DownLeft, DownRight, UpLeft, UpRight
};

class Spell
{
public:
    Spell(float playerPosX, float playerPosY);
    ~Spell();
    
    virtual void updatePos();
    sf::Sprite getSprite();
    
    float getSpeed();
    float getPosX();
    float getPosY();
    bool getActive();
    sf::Texture getTexture();
    
    void setPosX(float positionX);
    void setPosY(float positionY);

protected:
    float startX, startY, posX, posY, fastSpeed, slowSpeed;
    float startPosXModifier, startPosYModifier;
    sf::Sprite sprite;
    sf::Texture texture;
    bool active;
    
private:
};




// str.at(i) == 'a' 

#endif /* defined(__RPG_Game_SFML__Spell__) */
