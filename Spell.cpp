#include "Spell.h"

Spell::Spell(float playerPosX, float playerPosY) {
    startX = posX = playerPosX;
    startY = posY = playerPosY;
    fastSpeed = (1 * (sqrt(3)/2));
    slowSpeed = (1 * (0.5));
}

Spell::~Spell() {
    cout << "Spell deleted" << endl;
//    sprite.~Sprite();
//    texture.~Texture();
}

float Spell::getPosX() { return posX; }
float Spell::getPosY() { return posY; }
sf::Sprite Spell::getSprite() { return sprite; }
sf::Texture Spell::getTexture() { return texture; }

bool Spell::getActive() {
    if(posX < startX - 500 || posX > startX + 500 || posY < startY - 500 || posY > startY + 500) {
        active = false;
    }
    return active;
}

void Spell::setPosX(float positionX) { posX = positionX; }
void Spell::setPosY(float positionY) { posX = positionY; }

void Spell::updatePos() { std::cout << "Spell::updatePos() is not supposed to do anything" << std::endl; }