#include "Entity.h";
#include "Goblin.h";
#include <vector>
class EntityLoader {
public:
	EntityLoader();
	void loadEntities();
	void updateEntities();
	Entity& getEntity(int i);
private:
	std::vector<Entity> entities;
};

EntityLoader::EntityLoader() {
	loadEntities();
}

void EntityLoader::loadEntities() {
	Goblin g1;
}

void EntityLoader::updateEntities() {

}

Entity& EntityLoader::getEntity(int i) {
	return entities[i];
}
