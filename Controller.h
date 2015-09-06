#ifndef __RPG_Game_SFML__Controller__
#define __RPG_Game_SFML__Controller__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
//#include "Spell.h"
#include "WindStrike.h"

using namespace std;

class Controller
{
public:
    Controller();
    
    void handleInput(Player* player);
    void updateSpells();
    
    void draw(sf::RenderTexture& rTexture);
    int getSpellAmount();
    
private:
    pair<float, float> getConverted(float x, float y);
    
    sf::Clock clock;
    sf::Time timer;
    sf::Time lastShot;
    
    int removeCount, amountOfSpells;
    float moveX, moveY;
    float fastMove, slowMove;
    
    //Projectiles
    Direction direction;
    std::vector<Spell*> activeSpells;
    sf::RenderTexture spellTexture;
};

#endif /* defined(__RPG_Game_SFML__Controller__) */
