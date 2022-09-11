#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <map>
class Map : public sf::Drawable, public sf::Transformable {
public:
	Map();
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	int* getMapFile() { return tileMap; }
private:
	void parseMapFile(std::string filename);
	void parseMapTileIDFile(std::string filename);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		states.texture = &tileset_texture;
		target.draw(vertices, states);
	}
	//const int MAP_WIDTH = 100, MAP_HEIGHT = 100;
	int* tileMap;
	std::map<char, std::string> tileIDMap;

	sf::Texture tileset_texture;
	sf::VertexArray vertices;
};

Map::Map() {
	tileMap = new int[128];
	parseMapFile("mapfiles/mapfile2.txt");
	parseMapTileIDFile("mapfiles/map_tile_id_file.txt");
}

void Map::parseMapTileIDFile(std::string filename) {
	std::string fileText;
	std::fstream file;
	file.open(filename);
	while (std::getline(file, fileText)) {
		char id;
		std::string name;
		for (int i = 0; i < fileText.length(); i++) {
			if (i == 0) id = fileText[i];
			else name += fileText[i];
		}
		tileIDMap[id] = name;
	}
	file.close();

	/*
	for (auto i : tileIDMap) {
		std::cout << "id: " << i.first << "   " << "name: " << i.second << std::endl;
	}
	*/

}

void Map::parseMapFile(std::string filename) {
	std::string fileText;
	std::fstream file;
	file.open(filename);
	int ptr = 0;
	while (std::getline(file, fileText)) {
		for (int i = 0; i < fileText.length(); i++) {
			tileMap[ptr] = fileText[i];
			ptr++;
		}
	}
	file.close();
}

bool Map::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
	if (!tileset_texture.loadFromFile(tileset)) return false;

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width * height * 4);

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j) {
			// get the current tile number
			int tileNumber = tiles[i + j * width]; //0=grass,1=water,etc

			// find its position in the tileset texture
			int tu = tileNumber % (tileset_texture.getSize().x / tileSize.x); //3 %  (256 / 32)
			int tv = tileNumber / (tileset_texture.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
}



