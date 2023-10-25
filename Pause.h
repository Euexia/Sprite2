#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pause {
private:
    sf::Font font;
    sf::Text pauseText;

public:
    Pause() {
        if (!font.loadFromFile("assets/fonts/monogram.ttf")) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }

        pauseText.setFont(font);
        pauseText.setString("Appuyez sur P pour continuer\nAppuyez sur Q pour retourner au menu");
        pauseText.setCharacterSize(40);
        pauseText.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 40);  // Ajustez la position selon vos préférences
    }

    void display(sf::RenderWindow& window) {
        window.clear();
        window.draw(pauseText);
        window.display();

        bool isPaused = true;

        while (isPaused) {
            sf::Event event;


            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::P) {
                        isPaused = false;  // Quitte le menu de pause
                    }
                    else if (event.key.code == sf::Keyboard::Q) {
                        
                        return;  // Retournez au menu principal
                    }
                }
            }
        }
    }
};

