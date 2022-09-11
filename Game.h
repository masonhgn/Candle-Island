#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Map.h";
#include "variables.cpp"
class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool keyDown);
	Player p;
	Map m;
private:
	sf::RenderWindow window;
	

	bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false, pressed = false;
	float playerVelocity = 120;
	sf::Time frameTime = sf::seconds(1.f / 60.f);
	const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
};

/*
const int level[] =
{
	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
	0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
	0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
	0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
	2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
};
*/

Game::Game() : window(sf::VideoMode(1200,800), "Mason's Window") , p(), m() {
	
	if (!m.load("sprites/spritesheet.png", sf::Vector2u(32, 32), level, 128, 128)) {
		std::cout << "error, couldn't load tileset...";
		exit(EXIT_FAILURE);
	}
	

}

void Game::run() {
	sf::Clock clock;
	sf::Time updateTime = sf::Time::Zero;
	while (window.isOpen()) {
		processEvents();
		updateTime += clock.restart(); //fixed time steps
		while (updateTime > frameTime) { 
			updateTime -= frameTime;
			processEvents();
			update(frameTime); //no matter what, this will always be given the same delta
		}
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: 
				window.close();
				break;
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
		}	
	}
}

void Game::update(sf::Time dt) {
	sf::Vector2f movement(0.f, 0.f);
	if (movingUp) movement.y -= playerVelocity;
	if (movingDown) movement.y += playerVelocity;
	if (movingLeft) movement.x -= playerVelocity;
	if (movingRight) movement.x += playerVelocity;
	p.playerSprite.move(movement * dt.asSeconds());
}

void Game::render() {
	window.clear();
	window.draw(m);
	window.draw(p.playerSprite);
	window.display();
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool keyDown) {
	if (key == sf::Keyboard::W) {
		movingUp = keyDown;
	}
	else if (key == sf::Keyboard::S) {
		movingDown = keyDown;
	}
	else if (key == sf::Keyboard::A) {
		movingLeft = keyDown;
	}
	else if (key == sf::Keyboard::D) {
		movingRight = keyDown;
	}
}