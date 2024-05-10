    cmake_minimum_required(VERSION 3.27)
    project(rpg)

    set(CMAKE_CXX_STANDARD 17)
    include_directories(Character)
    include_directories(Enemy)
    include_directories(Player)
    include_directories(Combat)

    add_executable(rpg main.cpp
            Character/Character.cpp
            Character/Character.h
            Player/Player.cpp
            Player/Player.h
            Enemy/Enemy.cpp
            Enemy/Enemy.h
            Combat/Combat.cpp
            Combat/Combat.h
            Utils.h
            Combat/Action.h)
