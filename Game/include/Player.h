#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include "Menu.h"


class Player {
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Vector2f velocity;
    const float speed = 0.04f; // Vitesse de déplacement

public:
    Player() {
        if (!playerTexture.loadFromFile("assets/player/img-player.png")) {
            std::cerr << "Erreur lors du chargement de l'image du joueur!" << std::endl;
        }
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(sf::Vector2f(100, 100)); // position de départ
    }

    // Fonction pour vérifier si le joueur a atteint un bord
    sf::Vector2i checkBounds() {
        if (playerSprite.getPosition().x < 0) return { -1, 0 };
        if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width > WINDOW_WIDTH - 10) return { 1, 0 };
        if (playerSprite.getPosition().y < 0) return { 0, -1 };
        if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height > WINDOW_HEIGHT - 10) return { 0, 1 };
        return { 0, 0 };  // Si aucun bord n'est atteint
    }

    void handleInput();

    void update();


    void setPosition(float x, float y);
    sf::Vector2f getPosition() const {
        return playerSprite.getPosition();
    }
    sf::FloatRect getBounds() const {
        return playerSprite.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window);
};