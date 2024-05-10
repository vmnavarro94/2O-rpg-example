#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <cstring>
using namespace std;
using namespace combat_utils;


bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

//costructor
Player::Player(char name[30], int health, int attack, int defense, int speed, char arm[20], int experience, int level) : Character(name, health, attack, defense, speed, true, arm, experience, level) {

}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "You have taken " << damage << " damage whit a "<< getArm() << endl;
    if (health <= 0) {
        cout << "You have died  GAME OVER " << endl;
    }
}


void Player::flee(vector<Enemy*> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "chance to flee " << chance << endl;
        if (fleed = chance > 90) {
            fleed = true;
        } else {
            cout << "You can't be fleed, fight homosexual " << endl;
        }
    }

    this->fleed = fleed;

}

void Player::emote() {
    cout<<"Jokes on you" << endl;
}


Character* Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose a target" << endl;
    int targetIndex = 0;
    for(int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;

    return enemies[targetIndex];
}

void Player::gainExperience(Enemy* enemy) {
    // Verificar si el enemigo está muerto
    if (enemy && enemy->health <= 0) {
        // Sumar la experiencia obtenida por derrotar al enemigo
        experience += enemy->experience;
        cout << "Player gained " << enemy->experience << " experience from enemy." << endl;
    }
}

//FUNCION PARA SUBIR DE NIVEL
void Player::LevelUp() {
    // Verificar si el jugador ha alcanzado o superado 100 de experiencia
    while (experience >= 100) {
        // Incrementar el nivel del jugador en 1
        level++;
        // Reducir 100 de experiencia
        experience -= 100;
    }
}

Action Player::takeAction(vector<Enemy*>enemies) {
    int option = 0;
    cout<<"////////////////"<<endl;
    cout<<"Choose an action"<<endl;
    cout<<"1. Attack"<<endl;
    cout<<"2. Flee"<<endl;

    cin >> option;
    Character* target = nullptr;


    Action myAction;

    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            //1.
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }


    return myAction;
}