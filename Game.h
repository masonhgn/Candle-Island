#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Map.h";
#include "variables.cpp"
#include "Goblin.h";
#include "Tree.h";
class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool keyDown);
	void updateCameraPosition();
	Player player;
	Map m;
	Tree t;
	Goblin g1;
private:
	sf::View mainView;
	sf::RenderWindow window;
	bool pressed = false;
	
	sf::Time frameTime = sf::seconds(1.f / 60.f);
	const int SCREEN_WIDTH = 900, SCREEN_HEIGHT = 700;
};



Game::Game() : window(sf::VideoMode(800,600), "Candle Island") , player(), m(), mainView(sf::FloatRect(400.f,300.f, 800.f, 600.f)) {
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
	player.update(dt);
	g1.update(dt);
	updateCameraPosition();
}

void Game::render() {
	window.clear();
	window.draw(m);
	window.setView(mainView);
	window.draw(t.sprite);
	window.draw(g1.sprite);
	window.draw(player.playerSprite);
	window.display();
}

void Game::updateCameraPosition() {
	mainView.setCenter(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y);
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool keyDown) {
	if (key == sf::Keyboard::W) {
		player.movingUp = keyDown;
	}
	else if (key == sf::Keyboard::S) {
		player.movingDown = keyDown;
	}
	else if (key == sf::Keyboard::A) {
		player.movingLeft = keyDown;
	}
	else if (key == sf::Keyboard::D) {
		player.movingRight = keyDown;
	}
	else if (key == sf::Keyboard::G) {
		t.cutDown();
	}
}