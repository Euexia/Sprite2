#include "Player.h"

void Player::handleInput() {
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

void Player::update() {
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

void Player::setPosition(float x, float y) {
    playerSprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(playerSprite);
}