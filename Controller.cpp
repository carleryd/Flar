#include "Controller.h"
#include <stdio.h>
#include <math.h>

Controller::Controller() {
    moveX = moveY = 0;
    timer = clock.getElapsedTime();
    lastShot = clock.getElapsedTime();
    fastMove = (10 * (sqrt(3)/2));
    slowMove = (10 * (0.5));
    direction = Down;
    spellTexture.create(200*40, 200*40);
    removeCount = 0;
}

void Controller::handleInput(Player* player) {
    auto currentTime = clock.getElapsedTime();
    if(timer.asMilliseconds() + 10 < currentTime.asMilliseconds()) {
        
        const bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        const bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        const bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        const bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        const bool fire = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
        
        
        // Movement
        if(up) {
            moveX += slowMove;
            moveY -= fastMove;
            if(left) direction = UpLeft;
            else if(right) direction = UpRight;
            else direction = Up;
        }
        if(down) {
            moveX -= slowMove;
            moveY += fastMove;
            if(left) direction = DownLeft;
            else if(right) direction = DownRight;
            else direction = Down;
        }
        if(left){
            moveX -= fastMove;
            moveY -= slowMove;
            if(down) direction = DownLeft;
            else if(up) direction = UpLeft;
            else direction = Left;
        }
        if(right) {
            moveX += fastMove;
            moveY += slowMove;
            if(down) direction = DownRight;
            else if(up) direction = UpRight;
            else direction = Right;
        }
        if(fire && lastShot.asMilliseconds() < currentTime.asMilliseconds() - 1000) {
            activeSpells.push_back(new WindStrike(direction,
                                                  player->getPosX() + getConverted((player->getWidth() - 40)/2, (player->getHeight() - 40)/2).first,
                                                  player->getPosY() + getConverted((player->getWidth() - 40)/2, (player->getHeight() - 40)/2).second));
//            cout << "pressed - stored, size: " << activeSpells.size() << endl;
            lastShot = currentTime;
        }
        
        player->setPos(player->getPosX() + moveX, player->getPosY() + moveY);
        
        if(moveX == 0 && moveY > 0) {       // 1: Moving downwards
            player->setSprite(0, 0, 50, 100);
        }
        else if(moveX == 0 && moveY < 0) {  // 2: Moving upwards
            player->setSprite(0, 100, 50, 100);
        }
        else if(moveX < 0 && moveY == 0) {  // 3: Moving left
            player->setSprite(0, 200, 50, 100);
        }
        else if(moveX > 0 && moveY == 0) {  // 4: Moving right
            player->setSprite(0, 300, 50, 100);
        }
        else if(moveX < 0 && moveY > 0) {   // 5: Moving down to the left
            player->setSprite(0, 400, 50, 100);
        }
        else if(moveX > 0 && moveY > 0) {   // 6: Moving down to the right
            player->setSprite(0, 500, 50, 100);
        }
        else if(moveX < 0 && moveY < 0) {   // 7: Moving up to the left
            player->setSprite(0, 600, 50, 100);
        }
        else if(moveX > 0 && moveY < 0) {   // 8: Moving up to the right
            player->setSprite(0, 700, 50, 100);
        }
        moveX = moveY = 0;
        timer = currentTime;
    }
    updateSpells();
}

void Controller::updateSpells() {
    vector<Spell*> marked;
    for(int i = 0; i < activeSpells.size(); i++) {
        if(activeSpells[i]->getActive()) {
            activeSpells[i]->updatePos();
        }
        else {
//            cout << "Before - size: " << activeSpells.size() << " i: " << i << endl;
//            marked.push_back(activeSpells[i]);
//            delete activeSpells[i]; // slight memory leak - perhaps delete sprite/texture?
            activeSpells.erase(activeSpells.begin() + i);
//            delete temp;
            i--;
            removeCount++;
//            cout << "removeCount: " << removeCount << endl;
        }
    }
/*
    for(int i = 0; i < marked.size(); i++) {
        cout << marked[i]->getSprite().getGlobalBounds().height << endl;
        delete marked[i];
    }*/
    //cout << "After size: " << activeSpells.size() << endl;
}

pair<float, float> Controller::getConverted(float x, float y) {
    if(x == 0)
        return pair<float, float>(-y * 0.5, y * (sqrt(3)/2));
    if(y == 0)
        return pair<float, float>(x * (sqrt(3)/2), -x * 0.5);
    if(x > 0) {
        if(y > 0)
            return pair<float, float>(x * (sqrt(3)/2) - y * 0.5, -x * 0.5 + y * (sqrt(3)/2));
        if(y < 0)
            return pair<float, float>(x * (sqrt(3)/2), y * 0.5);
    }
    if(x < 0) {
        if(y > 0)
            return pair<float, float>(x * (sqrt(3)/2), y * 0.5);
        if(y < 0)
            return pair<float, float>(x * 0.5, y * (sqrt(3)/2));
    }
//    return pair<float, float>(-y * 0.5 + x * (sqrt(3)/2), y * (sqrt(3)/2) - x * 0.5);
    return pair<float, float>(0, 0);
}

void Controller::draw(sf::RenderTexture& rTexture) {
    for(int i = 0; i < activeSpells.size(); i++) {
        rTexture.draw(activeSpells[i]->getSprite());
    }
//    spellTexture.display();
    
//    return sf::Sprite(spellTexture.getTexture());
}
