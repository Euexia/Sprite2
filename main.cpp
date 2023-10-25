#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Scene.h"
#include "Menu.h"
#include <iostream>
#include <windows.h>
#include "Pause.h"




class Player {
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Vector2f velocity;
    const float speed = 0.2f; // Vitesse de déplacement

public:
    Player() {
        if (!playerTexture.loadFromFile("assets/player/img-player.png")) {
            std::cerr << "Erreur lors du chargement de l'image du joueur!" << std::endl;
        }
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(sf::Vector2f(100, 100)); // position de départ
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerSprite.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerSprite.move(0, speed);
        }
    }

    void update() {

        // Gestion des collisions avec les bords de la fenêtre
        // Haut
        if (playerSprite.getPosition().y < 0) {
            playerSprite.setPosition(playerSprite.getPosition().x, 0);
        }
        // Bas
        if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height > WINDOW_HEIGHT) {
            playerSprite.setPosition(playerSprite.getPosition().x, WINDOW_HEIGHT - playerSprite.getGlobalBounds().height);
        }
        // Gauche
        if (playerSprite.getPosition().x < 0) {
            playerSprite.setPosition(0, playerSprite.getPosition().y);
        }
        // Droite
        if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width > WINDOW_WIDTH) {
            playerSprite.setPosition(WINDOW_WIDTH - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(playerSprite);
    }
};



class Game {
private:
    sf::RenderWindow window;
    Player player;
    Menu mainMenu;
    Pause pauseMenu;  // Instanciez votre menu de pause ici
    bool isPaused = false;

public:
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Portail Dimensionnel") {}

    void run() {
        int menuChoice = mainMenu.run(window);

        switch (menuChoice) {
        case 0:  // Play
            gameLoop();
            break;

        case 1:  // Settings
            break;

        case 2:  // Quit
            window.close();
            return;

        default:
            break;
        }
    }

    void gameLoop() {
        while (window.isOpen()) {
            handleEvents();
            if (!isPaused) {
                update();
                render();
            }
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Gestion du menu de pause
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                isPaused = !isPaused;
                if (isPaused) {
                    pauseMenu.display(window);
                }
            }
        }

        if (!isPaused) {
            player.handleInput();
        }
    }

    void update() {
        player.update();
    }

    void render() {
        window.clear();
        player.draw(window);
        window.display();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
