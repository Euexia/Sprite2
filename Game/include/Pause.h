#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include "Menu.h"

class Pause {
private:
    sf::Font font;
    sf::Text title;  // Titre "Pause"
    std::vector<sf::Text> options;
    int selectedIndex = 0;

public:
    Pause() {}
    Pause(sf::Font& menuFont) {
        font = menuFont;
        std::string fontPath = "assets/fonts/monogram.ttf";

        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        // Créez le texte "Pause" (titre)
        title.setFont(font);
        title.setString("Pause");
        title.setCharacterSize(60);
        title.setPosition(WINDOW_WIDTH / 2 - 60, 100);

        std::string strOptions[] = { "Reprendre", "Recommencer", "Quitter" };
        for (int i = 0; i < 3; i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(strOptions[i]);
            text.setCharacterSize(40);
            text.setPosition(WINDOW_WIDTH / 2 - 50, 200 + i * 60);
            options.push_back(text);
        }
    }

    void setSelectedIndex(int index) {
        selectedIndex = index;
    }

    int run(sf::RenderWindow& window) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();

            // Dessinez le titre "Pause"
            window.draw(title);

            for (size_t i = 0; i < options.size(); i++) {
                if (i == selectedIndex) {
                    options[i].setFillColor(sf::Color::Red);
                }
                else {
                    options[i].setFillColor(sf::Color::White);
                }
                window.draw(options[i]); // Dessinez les options dans la fenêtre
            }

            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                selectedIndex = (selectedIndex + 1) % options.size();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                return selectedIndex;
            }
        }

        return -1;
    }
};