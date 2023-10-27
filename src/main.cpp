#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>

#include "GameObject.h"
#include "Scene.h"
#include "Menu.h"
#include "SettingsMenu.h"
#include "Map.h"
#include "Pause.h"
#include "Attack_turn.h"
#include "Player.h"
#include "Game.h"


int main() {
    Game game;
    game.run();

    return 0;
}