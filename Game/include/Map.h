#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"



class Map {
private:
    sf::RectangleShape background; // Rectangle utilis� pour dessiner le fond color�
    sf::Color colors[3][3]; // Matrice 3x3 des couleurs


public:
    Map() {
        background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)); // Ajustez ces valeurs selon la taille de votre fen�tre

        // Initialisation des couleurs pour chaque cellule de la matrice
        // Vous pouvez ajuster ces couleurs selon vos pr�f�rences
        colors[0][0] = sf::Color::Red;
        colors[0][1] = sf::Color::Green;
        colors[0][2] = sf::Color::Blue;
        colors[1][0] = sf::Color::Yellow;
        colors[1][1] = sf::Color::Magenta;
        colors[1][2] = sf::Color::Cyan;
        colors[2][0] = sf::Color::White;
        colors[2][1] = sf::Color::Black;
        colors[2][2] = sf::Color(128, 128, 128); // Gris

        // Initialisation de la couleur par d�faut
        background.setFillColor(colors[1][1]); // Centre de la matrice
    }

    // Mettre � jour la couleur de fond selon la position de la cam�ra
    void updateBackground(const sf::Vector2i& cameraPosition);

    void draw(sf::RenderWindow& window);

};
