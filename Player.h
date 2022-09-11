#include <SFML/Graphics.hpp>
#include <iostream>
class Player{
public:
	Player();
	sf::Sprite playerSprite;
private:
	sf::Texture playerTexture;
	sf::Vector2u playerSize;
};

Player::Player() : playerTexture(), playerSprite() {
	if (!playerTexture.loadFromFile("sprites/player.png")) {
		std::cout << "error loading player sprite...";
	}
	playerSize = playerTexture.getSize();
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(449.f, 100.);
}

