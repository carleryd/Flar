#include "Player.h"
#include "ResourcePath.hpp"


Player::Player(int windowWidth, int windowHeight) {
    //Init
    std::string path = resourcePath();
    if(!texture.loadFromFile(path + "gnome_mage_spritesheet.png")) std::cout << "Cannot load player image" << std::endl;
    
    sprite = new sf::Sprite(texture);
    sprite->move(windowWidth/2/* - texture.getSize().x/2*/, windowHeight/2/* - texture.getSize().y/2*/);
    sprite->setTextureRect(sf::Rect<int>(0, 0, 50, 100));
    sprite->rotate(30);
    
    posX = windowWidth/2;
    posY = windowHeight/2;
    movedX = 0;
    movedY = 0;
    width = 50;
    height = 100;
}

void Player::draw(sf::RenderWindow& window) {
    sprite->move(movedX, movedY);
    window.draw(*sprite);
}

float Player::getPosX() { return posX; }
float Player::getPosY() { return posY; }
float Player::getMovedX() { return movedX; }
float Player::getMovedY() { return movedY; }
int Player::getWidth() { return width; }
int Player::getHeight() { return height; }
bool Player::getHasMoved() { return hasMoved; }
sf::Sprite* Player::getSprite() { return sprite; }

void Player::setSprite(int startX, int startY, int width, int height) {
    sprite->setTextureRect(sf::IntRect(startX, startY, width, height));
}

void Player::setPos(float x, float y) {
    movedX = x - posX;
    movedY = y - posY;
    posX = x;
    posY = y;
    hasMoved = true;
}

void Player::setNotMoving() {
    if(movedX != 0 || movedY != 0) {
        movedX = movedY = 0;
        hasMoved = false;
    }
}
