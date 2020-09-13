#include "BoardScreen.h"
#include "ManageAssets.h"

GameScreen::GameScreen()
{
}

GameScreen::GameScreen(StateManager* stateManager) :
	stateManager(stateManager)
{
}

GameScreen::~GameScreen()
{
}

sf::Sprite GameScreen::background(AssetManager::getInstance()->getTexture("background.png"));

void GameScreen::renderScreen(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	window.draw(background);
}

void GameScreen::handleMouseClick(sf::Vector2f mousePosition)
{
}

void GameScreen::handleTextEntry(sf::Event::TextEvent textEvent)
{
}
