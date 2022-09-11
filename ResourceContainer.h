#include <string>


template <typename Resource, typename Identifier>
class ResourceContainer {
public:
	void load(Identifier id, const std::string& f);
	Resource& get(Identifier id);
	typedef ResourceContainer<sf::Texture, Textures::ID> TextureContainer;
private:
	std::map<Identifier, std::unique_ptr<Resource>> resourcemap;
};

template<typename Resource, typename Identifier>
void ResourceContainer<Resource, Identifier>::load(Identifier id, const std::string& f) {
	std::uniqueptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(f)) {
		throw(std::runtime_error("ResourceContainer::load failed to load file location: " + f));
	}
	auto inserted = resourcemap.insert(std:make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceContainer<Resource, Identifier>::get(Identifier id) {
	auto found = resourcemap.find(id);
	assert(found != resourcemap.end());
	return *found->second;
}


