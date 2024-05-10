#ifndef Jueguito_ENEMY_H
#define Jueguito_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"


struct Action;
class Player;

class Enemy: public Character {

public:
    //atributos personales de enemigo
    int MaxHealth;

public:

    //metodos:

    Enemy(char[30] , int, int, int, int, char[20],int, int );
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> player);



};


#endif