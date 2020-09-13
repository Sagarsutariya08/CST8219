#pragma once
#include "GamePlayer.h"

class GameScreen;

class StateManager
{
public:
	StateManager();
	~StateManager();

	enum class Screen
	{
		Gameboard,
		EndScreen
	};

	void switchScreen(Screen newScreen);
	std::vector<Player*> getPlayers();
	void setPlayers(std::vector<Player*> players);
	void setBoardSize(sf::Vector2u boardSize);
	void clearSettings();

	GameScreen* currentScreen;
	GameScreen* nextScreen;

	struct GameSettings
	{
		GameSettings() {};
		GameSettings(std::vector<Player*> players) : players(players) {};
		GameSettings(std::vector<Player*> players, sf::Vector2u boardSize) : players(players), boardSize(boardSize) {};
		~GameSettings()
		{
			for (size_t i = 0; i < players.size(); i++)
			{
				delete players[i];
			}
			players.clear();
		}
		std::vector<Player*> players;
		sf::Vector2u boardSize;
	};

	GameSettings* gameSettings;
};