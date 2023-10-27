#include "Map.h"

void Map::updateBackground(const sf::Vector2i& cameraPosition) {
	background.setFillColor(colors[cameraPosition.x][cameraPosition.y]);
}
void Map::draw(sf::RenderWindow& window) {
    window.draw(background);
}