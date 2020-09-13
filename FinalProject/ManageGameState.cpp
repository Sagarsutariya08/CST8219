#include "ManageGameState.h"
#include "BoardScreen.h"
#include "Board.h"
#include "ScorePage.h"

StateManager::StateManager() :
	gameSettings(new GameSettings())
{
}

StateManager::~StateManager()
{
	delete currentScreen;
	delete nextScreen;
	delete gameSettings;
}

void StateManager::switchScreen(Screen newScreen)
{
	if (nextScreen != nullptr)
	{
		delete nextScreen;
		nextScreen = nullptr;
	}

	switch (newScreen)
	{
	case Screen::Gameboard:
		nextScreen = new GameBoard(this);
		break;
	case Screen::EndScreen:
		nextScreen = new EndScreen(this);
		break;
	default:
		break;
	}

	if (nextScreen != nullptr)
	{
		std::swap(currentScreen, nextScreen);
	}
}

std::vector<Player*> StateManager::getPlayers()
{
	return gameSettings->players;
}

void StateManager::setPlayers(std::vector<Player*> players)
{
	gameSettings->players = players;
}

void StateManager::setBoardSize(sf::Vector2u boardSize)
{
	gameSettings->boardSize = boardSize;
}

void StateManager::clearSettings()
{
	gameSettings->players.clear();
	gameSettings->boardSize = { 4, 4 };
}
