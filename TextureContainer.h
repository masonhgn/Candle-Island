#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <assert.h>
namespace Textures {
	enum ID { 
		Landscape, Goblin, Spell, FlyingToads
		//we are housing our game entities in an enum as ID's, so we can access them later for use as textures.
		//since this is in the namespace Textures, this allows for textures to be very easily distinguishable as Textures::Goblin. We can tell that is a texture.
	};
}
		//unique ptrs allow for easy allocation and deallocation when objects go in and out of scope.
		//unique ptrs automatically call the delete operator in their destructor. This encourages RAII.
		//a std::unique_ptr<T> instance is the only owner of the T object it points to, which is why it is called a unique pointer.
class TextureContainer {
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> texturemap;
public:
	void load(Textures::ID id, const std::string& filename);
	const sf::Texture& get(Textures::ID id);
};


void TextureContainer::load(Textures::ID id, const std::string& filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename)) {
		throw std::runtime_error("TextureContainer::load - failed to load from file location: " + filename);
	}
	auto inserted = texturemap.insert(std::make_pair(id, std::move(texture)));
	assert(inserted.second);
}

const sf::Texture& TextureContainer::get(Textures::ID id) {
	auto found = texturemap.find(id);
	assert(found != texturemap.end());
	//assert will stop the program in debug mode if the given expression is false. In release mode, it will not do anything.
	//this will help for better exception handling and will in this case specifically make sure that we do not call a value in our map that we have not inserted.
	return *found->second;
}