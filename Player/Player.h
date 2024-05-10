
#ifndef Jueguito_PLAYER_H
#define Jueguito_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

struct Action;
class Enemy;

class Player: public Character {

    //Constructor
public:
    Player(char _name[30], int _health, int _attack, int _defense, int _speed, char _arm[20], int _experience, int _level);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    void gainExperience(Enemy* enemy);

    //Funcion para que aumente su nivel /////////
    void LevelUp();

    Character* getTarget(vector<Enemy*> enemies);
    void flee(vector<Enemy*> enemies);
    void emote();
    Action takeAction(vector<Enemy*> enemies);

};



#endif