#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>



const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;


class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex = 0;
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackgroundSprite;

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

        nlohmann::json jsonData;
        std::ifstream jsonFile("Game/assets/tiles/map.json"); //map
        if (jsonFile.is_open()) {
            jsonFile >> jsonData;

            // Récupérez le chemin de l'image du fond du menu depuis le JSON
            std::string menuBackgroundImagePath = jsonData["menuBackgroundImage"].get<std::string>();

            // Chargez l'image du fond du menu
            if (!menuBackgroundTexture.loadFromFile(menuBackgroundImagePath)) {
                std::cerr << "Erreur lors du chargement de l'image de fond du menu!" << std::endl;
            }

            menuBackgroundSprite.setTexture(menuBackgroundTexture);
            menuBackgroundSprite.setScale(
                static_cast<float>(WINDOW_WIDTH) / menuBackgroundTexture.getSize().x,
                static_cast<float>(WINDOW_HEIGHT) / menuBackgroundTexture.getSize().y
            );

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
    }

    int run(sf::RenderWindow& window) {
        window.clear();

        while (window.isOpen()) {
            window.clear(sf::Color::White);

            // Dessinez le fond du menu en premier
            window.draw(menuBackgroundSprite);

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        selectedIndex = (selectedIndex + 1) % options.size();
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

