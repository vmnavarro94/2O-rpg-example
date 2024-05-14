
#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant: participants) {
        if(participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}



void Combat::doCombat() {
    prepareCombat();

    // Este while es una iteración por ronda
    while (enemies.size() != 0 && teamMembers.size() != 0) {
        registerActions();
        executeActions();
    }
    // Verifica quién ganó el combate
    if (enemies.size() == 0) {
        cout << "GANASTE... juego terminado" << endl;

        // Iterar a través de la lista de enemigos
        for (Enemy* enemy : enemies) {
            // Verificar si el enemigo está muerto
            if (enemy->health <= 0) {
                // Imprime la experiencia del enemigo derrotado
                cout << "el enemigo obtuvo" << enemy->experience << " total de experiencia." << endl;
            }
        }
        // Iterar a través de todos los miembros del equipo
        for (Player* player : teamMembers) {
            // Imprimir la experiencia total ganada por el jugador
            cout << "el personaje " << player->getName() << " ah ganado " << player->experience << " total de experiencia." << endl;
        }
    } else {
        cout << "Los enemigos ganaron el combate... Juego terminado." << endl;
    }


    //IMPRIMIR Atributos con el nivel aumentadp
    for (Player *player: teamMembers) {
        cout << "Nivel avanzado. " << endl;
        cout << player->health << endl;
        cout << player->attack << endl;
        cout << player->defense << endl;
    }
}



void Combat::increaseEnemyStats(int points) {
    // DAR LOS PUNTOS A LOS ENEMIGOS
    for (Enemy *enemy: enemies) {

        // Aumentar atributos
        int healthIncrease = points / 3;
        int attackIncrease = points / 3;
        int defenseIncrease = points - healthIncrease - attackIncrease;
        enemy->health += healthIncrease;
        enemy->attack += attackIncrease;
        enemy->defense += defenseIncrease;
    }
}

void Combat::registerActions() {
    vector<Character*>::iterator participant = participants.begin();
    //Una iteracion por turno de cada participante (player y enemigo)
    while(participant != participants.end()) {
        Character* target = nullptr;
        Action currentAction;
        if((*participant)->getIsPlayer()) {
            currentAction = ((Player*)*participant)->takeAction(enemies);
        }
        else {
            currentAction = ((Enemy*)*participant)->takeAction(teamMembers);
        }
        actions.push(currentAction);
        participant++;
    }
}

void Combat::executeActions() {
    //Aqui se ejecutan las acciones
    while(!actions.empty()) {
        Action currentAction = actions.top();
        currentAction.action();
        checkForFlee(currentAction.subscriber);
        if(currentAction.target!= nullptr)
        {
            checkParticipantStatus(currentAction.subscriber);
            checkParticipantStatus(currentAction.target);
            actions.pop();
        }
        else{
            while (!actions.empty()) {
                actions.pop();
            }
        }


    }
}

void Combat::checkParticipantStatus(Character* participant) {
    if(participant->getHealth() <= 0) {
        if(participant->getIsPlayer()) {
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end());
        }
        else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::checkForFlee(Character *character) {
    // Verificar si  murio para que no escape una vez ya muerto
    if (character->getHealth() <= 0) {
        return; //
    }
    bool fleed = character->hasFleed();
    if (fleed) {
        if (character->getIsPlayer()) {
            cout << "has abandonado el campo de batalla" << endl;
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), character), teamMembers.end());
        } else {
            cout << character->getName() << " ah abandonado el campo de batalla" << endl;
            enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), character), participants.end());
    }
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString()  + "\n";
    }
    return result;
}