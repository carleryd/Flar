#include "WindStrike.h"
#include "ResourcePath.hpp"

WindStrike::WindStrike(Direction direction, float playerPosX, float playerPosY) : Spell(playerPosX, playerPosY) {
    //std::cout << "Player WindStrike::Windstrike(...) X: " << playerPosX << " Y: " << playerPosY << std::endl;

    std::string spellPath = resourcePath();
    active = true;
    
    fastSpeed *= 5;
    slowSpeed *= 5;

    startPosXModifier = 100 * (0.5);
    startPosYModifier = 100 * (sqrt(3)/2); // 0.87

    spellMoveX = spellMoveY = 5;
    switch(direction) {
        case Down:
            spellMoveX = -slowSpeed;
            spellMoveY = fastSpeed;
            startPosXModifier *= -1;
            startPosYModifier *= 1;
            spellPath += "wind_strike/wind_strike_front.png";
            break;
        case Up:
            spellMoveX = slowSpeed;
            spellMoveY = -fastSpeed;
            startPosXModifier *= 1;
            startPosYModifier *= -1;
            spellPath += "wind_strike/wind_strike_back.png";
            break;
        case Left:
            spellMoveX = -fastSpeed;
            spellMoveY = -slowSpeed;
            spellPath += "wind_strike/wind_strike_left.png";
            break;
        case Right:
            spellMoveX = fastSpeed;
            spellMoveY = slowSpeed;
            spellPath += "wind_strike/wind_strike_right.png";
            break;
        case DownLeft:
            spellMoveX = - slowSpeed - fastSpeed;
            spellMoveY = fastSpeed - slowSpeed;
            spellPath += "wind_strike/wind_strike_front.png"; // Fix texture
            break;
        case DownRight:
            spellMoveX = - slowSpeed + fastSpeed;
            spellMoveY = fastSpeed + slowSpeed;
            spellPath += "wind_strike/wind_strike_front.png"; // Fix texture
            break;
        case UpLeft:
            spellMoveX = slowSpeed - fastSpeed;
            spellMoveY = -fastSpeed - slowSpeed;
            spellPath += "wind_strike/wind_strike_front.png"; // Fix texture
            break;
        case UpRight:
            spellMoveX = slowSpeed + fastSpeed;
            spellMoveY = -fastSpeed + slowSpeed;
            spellPath += "wind_strike/wind_strike_front.png"; // Fix texture
            break;
            
        default:
            std::cout << "No valid direction input given to castSpell(...)!" << std::endl;
            break;
    }

    if(!texture.loadFromFile(spellPath)) std::cout << "Cannot load WindStrike image" << std::endl;
    sprite.setTexture(texture);
    sprite.rotate(30);
    sprite.move(startX, startY);
    
    
//    std::cout << spellMoveX << " " << spellMoveY << std::endl;
}

void WindStrike::updatePos() {
    posX += spellMoveX;
    posY += spellMoveY;
//    std::cout << spellMoveX << " " << spellMoveY << std::endl;
    sprite.move(spellMoveX, spellMoveY);
}
