#include <SFML/Graphics.hpp>
#include "SceneNode.h"
class Entity : public SceneNode {
public:
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float velX, float velY);
	sf::Vector2f getVelocity() const;
	//typedef ResourceContainer<sf::Texture, Textures::ID> TextureContainer;
private:
	sf::Vector2f velocity;
};

void Entity::setVelocity(sf::Vector2f vel) { velocity = vel; }

void Entity::setVelocity(float velX, float velY) { 
	velocity.x = velX; 
	velocity.y = velY;
}

sf::Vector2f Entity::getVelocity() const { return velocity; }