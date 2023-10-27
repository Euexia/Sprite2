#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <windows.h>
#include <fstream>
#include <iostream>
#include "Menu.h"

class SettingsMenu {
private:
    sf::Font font;
    std::vector<sf::Text> settingsOptions;
    int selectedIndex = 0;

public:
    SettingsMenu() {
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        std::string strOptions[] = { "Volume", "Effacer Sauvegarde", "Retour au Menu" };
        for (int i = 0; i < 3; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(strOptions[i]);
            text.setCharacterSize(40);
            text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60); // Ajustez la position selon vos préférences
            settingsOptions.push_back(text);
        }
    }

    int run(sf::RenderWindow& window) {
        while (window.isOpen()) {
            window.clear(sf::Color::White);

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedIndex = (selectedIndex - 1 + 3) % 3;
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        selectedIndex = (selectedIndex + 1) % 3;
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        return selectedIndex;
                    }
                }
            }

            window.clear();
            for (int i = 0; i < 3; i++) {
                if (i == selectedIndex) {
                    settingsOptions[i].setFillColor(sf::Color::Red);
                }
                else {
                    settingsOptions[i].setFillColor(sf::Color::White);
                }
                window.draw(settingsOptions[i]);
            }

            window.display();
        }

        return -1;
    }
};
