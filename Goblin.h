#include "Entity.h"
#include <iostream>
#include <cstdlib>

namespace Textures {
	enum ID {
		Green,
		Red,
	};
}

class Goblin :public Entity {
public:
	Goblin();
	sf::Sprite sprite;
	void update(sf::Time dt);
	void automatedMovement();
	void randomMove();
	float getX() { return x; }
	float getY() { return y; }
	int tileX() { return x / 32; }
	int tileY() { return y / 32; }
	
private:
	bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;
	sf::Texture texture;
	sf::Vector2u size;
	int healthPoints, level;
	float x, y;
	int velocity;
};

Goblin::Goblin() : sprite(), texture() {
	healthPoints = 10;
	velocity = 100;
	level = 2;
	if (!texture.loadFromFile("sprites/goblin.png")) {
		std::cout << "error loading player sprite...";
	}
	size = texture.getSize();
	sprite.setTexture(texture);
	sprite.setPosition(100.f, 100.f);
	x = sprite.getPosition().x, y = sprite.getPosition().y;
	automatedMovement();
}

void Goblin::update(sf::Time dt) {
	sf::Vector2f movement(0.f, 0.f);
	if (movingUp) movement.y -= velocity;
	if (movingDown) movement.y += velocity;
	if (movingLeft) movement.x -= velocity;
	if (movingRight) movement.x += velocity;
	sprite.move(movement * dt.asSeconds());
	x = sprite.getPosition().x, y = sprite.getPosition().y;
}

void Goblin::randomMove() {
	//int randTime = rand() % 10000 + 2000;
	//int randDir = rand() % 3;


}

void Goblin::automatedMovement() {

}

