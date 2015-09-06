#ifndef __RPG_Game_SFML__WindStrike__
#define __RPG_Game_SFML__WindStrike__

#include <iostream>
#include "Spell.h"

class WindStrike : public Spell
{
public:
    WindStrike(Direction direction, float playerPosX, float playerPosY);
    ~WindStrike() { /*std::cout << "WindStrike destroyed" << std::endl;*/ }
    
    void updatePos();
//    sf::Sprite getSprite();
    
private:
    float spellMoveX, spellMoveY;
};

#endif /* defined(__RPG_Game_SFML__WindStrike__) */
