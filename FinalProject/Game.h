#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "BoardScreen.h"
#include "GamePlayer.h"

class StateManager;

class Game
{
public:
	Game();
	~Game();

	void run();

	GameScreen* currentScreen;
	GameScreen* nextScreen;

	enum class Screen
	{
		StartScreen,
		Gameboard,
		EndScreen
	};

private:
	sf::RenderWindow window;

	void processInput();
	void update(sf::Time deltaTime);
	void render();

	void renderScreen();
	void handleMouseClick(sf::Vector2f mousePosition);
	void handleTextEntry(sf::Event::TextEvent textEvent);
	void switchScreen(Screen newScreen);

	StateManager* stateManager;
};