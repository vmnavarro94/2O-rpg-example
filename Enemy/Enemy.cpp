#include "Enemy.h"
#include <iostream>

using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}


//costructor de ENEMY
Enemy::Enemy(char name[30], int health, int attack, int defense, int speed, char arm[20], int experience, int level) : Character(name, health, attack, defense, speed, false, arm, experience, level) {
}


void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout<<getName()<<" Ah muerto "<<endl;
    }
    else {
        cout<<getName()<<" has recibido " << damage << " daño con: "<<getArm()<< endl;
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {


    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}


Action Enemy::takeAction(vector<Player *> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;

    //TODO: generar una probabilidad

    Character* target = getTarget(player);
    srand(time(NULL));
    if (this->getHealth() < MaxHealth && rand() % 100 < 15){
        myAction.action = [this, target]() {
            this->fleed = true;
        };
    } else {
        myAction.target = target;
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }
    return myAction;
}