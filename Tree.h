#include <SFML/Graphics.hpp>
#include <iostream>
class Tree {
public:
	Tree();
	void cutDown();
	void regrow();
	sf::Sprite sprite;
private:
	sf::Texture texture;
	sf::Vector2u size;
	float x, y;
};


Tree::Tree() : sprite(), texture() {
	if (!texture.loadFromFile("sprites/tree.png")) {
		std::cout << "error loading tree sprite...";
	}
	size = texture.getSize();
	sprite.setTexture(texture);
	sprite.setPosition(1200.f, 1000.f);
	x = sprite.getPosition().x, y = sprite.getPosition().y;
}

void Tree::cutDown() {
	if (!texture.loadFromFile("sprites/tree_cutdown.png")) {
		std::cout << "error loading tree sprite...";
	}
}

void Tree::regrow() {
	if (!texture.loadFromFile("sprites/tree.png")) {
		std::cout << "error loading tree sprite...";
	}
}