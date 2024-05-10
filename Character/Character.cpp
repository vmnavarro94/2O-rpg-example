#include "Character.h"
#include <cstring> //para cadenas
#include<iostream>
#include <cstring>


//costructor con parametros
Character::Character(char _name[30], int _health, int _attack, int _defense, int _speed, bool _isPlayer, char _arm[20], int _experience, int _level) {
    strcpy_s(name, _name);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    fleed = false;
    strcpy_s(arm, _arm);
    experience = _experience;
    level = _level;
}


//metodos

void Character::setName(char _name[30]) {
    strcpy_s(name, _name);
}

char* Character::getName() {
    return name;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

int Character::getSpeed() {
    return speed;
}

char Character::toString() {
    cout << "Nombre: " << name
         << "\nSalud: " + to_string(health) + "\nAtaque: " + to_string(attack) + "\nDefensa: " + to_string(defense) +
            "\nVelocidad: " + to_string(speed);
}


bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::hasFleed() {
    return fleed;
}

void Character::setArm(char _arm[20]) {
    strcpy_s(arm, _arm);
}

char* Character::getArm() {
    return arm;
}

int Character::getExperience() {
    return experience;
}

int Character::getLevel() {
    return level;
}