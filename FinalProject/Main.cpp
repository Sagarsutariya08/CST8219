#include "Game.h"

Game::Game() :
	window(sf::VideoMode(WIDTH, HEIGHT), "Flipping Game"),
	stateManager(new StateManager())
{
	window.setFramerateLimit(FRAMERATE);
}

Game::~Game()
{
	delete stateManager;
}

void Game::run()
{
	sf::Clock clock;
	float playerListHeight = 500.f;
	float playerListIndent = WIDTH / 2.f;
	std::vector<Player*> players;
	Player* newPlayer = new Player("Computer");
	newPlayer->playerTag.setPosition(playerListIndent, playerListHeight);
	playerListHeight += newPlayer->playerTag.getCharacterSize() + 15.f;
	if (playerListHeight > 700.f)
	{
		playerListHeight = 500.f;
		playerListIndent += 150.f;
	}
	if (playerListIndent > 600.f)
	{
		playerListHeight = 500.f;
		playerListIndent = WIDTH / 2.f;
	}
	if (players.size() >= 10)
	{
		players.end()[-10]->playerTag.setFillColor(sf::Color::Transparent);
	}
	players.push_back(newPlayer);
	sf::Vector2u boardSize = { 4, 5 };
	stateManager->setPlayers(players);
	stateManager->setBoardSize(boardSize);
	stateManager->switchScreen(StateManager::Screen::Gameboard);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processInput();
		update(deltaTime);
		render();
	}
}

void Game::processInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				handleMouseClick(mousePosition);
			}
			break;
		case sf::Event::TextEntered:
			handleTextEntry(event.text);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	stateManager->currentScreen->updateScreen(deltaTime);
}

void Game::render()
{
	window.clear(sf::Color(255, 255, 255, 0));
	renderScreen();
	window.display();
}

void Game::renderScreen()
{
	stateManager->currentScreen->renderScreen(window);
}

void Game::handleMouseClick(sf::Vector2f mousePosition)
{
	stateManager->currentScreen->handleMouseClick(mousePosition);
}

void Game::handleTextEntry(sf::Event::TextEvent textEvent)
{
	stateManager->currentScreen->handleTextEntry(textEvent);
}

int main() {
	Game memory;
	memory.run();
}