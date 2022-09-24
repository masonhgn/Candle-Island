#include <SFML/Graphics.hpp>
#include <iostream>
class Player{
public:
	Player();
	void update(sf::Time dt);
	float getVelocity() { return velocity; }
	sf::Sprite playerSprite;
	bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;
	float getX() { return x; }
	float getY() { return y; }
	int tileX() { return x / 32; }
	int tileY() { return y / 32; }
private:
	float velocity = 170;
	sf::Texture playerTexture;
	sf::Vector2u playerSize;
	float x, y;
};

Player::Player() : playerTexture(), playerSprite() {
	if (!playerTexture.loadFromFile("sprites/player.png")) {
		std::cout << "error loading player sprite...";
	}
	playerSize = playerTexture.getSize();
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(450.f, 350.f);
	x = playerSprite.getPosition().x, y = playerSprite.getPosition().y;
}

void Player::update(sf::Time dt) {
	sf::Vector2f movement(0.f, 0.f);
	if (movingUp) movement.y -= velocity;
	if (movingDown) movement.y += velocity;
	if (movingLeft) movement.x -= velocity;
	if (movingRight) movement.x += velocity;
	playerSprite.move(movement * dt.asSeconds());
	x = playerSprite.getPosition().x, y = playerSprite.getPosition().y;
}

