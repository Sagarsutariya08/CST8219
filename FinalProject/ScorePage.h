#pragma once
#include "BoardScreen.h"
#include "GamePlayer.h"
#include "ShapeBtn.h"

class EndScreen :
	public GameScreen
{
public:
	EndScreen(StateManager* stateManager);
	~EndScreen();

	virtual void renderScreen(sf::RenderWindow& window);
	virtual void updateScreen(sf::Time deltaTime);
	virtual void handleMouseClick(sf::Vector2f mousePosition);
private:
	void displayPlayerScores();
	std::vector<Player*> players;
	Button* playAgainButton;
	void restartGame();
};