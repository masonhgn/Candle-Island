#include "Entity.h"
#include "ResourceContainer.h"

namespace Textures {
	enum ID {
		Green,
		Red,
	};
}

class Goblin :public Entity {
public:
	enum Type {
		Green,
		Red
	};
	Goblin(Type t);
private:
	Type type;
	sf::Sprite sprite;
	int healthPoints, level;
};

Goblin::Goblin(Type t) {
	healthPoints = 10;
	level = 1;
	if (type == Red) {
		healthPoints = 20;
		level = 16;
	}
	if (t == Green) {
		healthPoints = 12;
		level = 9;
	}
}



Textures::ID toTextureID(Goblin::Type t) {
	if (t == Goblin::Red) return Textures::Red;
	if (t == Goblin::Green) return Textures::Green;
}