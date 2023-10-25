#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;


class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex = 0;

public:
    Menu() {
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {  // Changez ce chemin pour pointer vers votre propre police
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        std::string strOptions[] = { "Play", "Settings", "Quit" };
        for (int i = 0; i < 3; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(strOptions[i]);
            text.setCharacterSize(40);  // Définit la taille du caractère à 40
            text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60); // Ajustez la position selon vos préférences
            options.push_back(text);
        }

    }

    int run(sf::RenderWindow& window) {
        window.clear();

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
                    options[i].setFillColor(sf::Color::Red);
                }
                else {
                    options[i].setFillColor(sf::Color::White);
                }
                window.draw(options[i]);
            }
            window.display();
        }
        return -1;
    }

};

