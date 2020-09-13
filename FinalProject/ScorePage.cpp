#include "ScorePage.h"
#include "Settings.h"

EndScreen::EndScreen(StateManager* stateManager) :
	GameScreen(stateManager),
	players(stateManager->gameSettings->players),
	playAgainButton(new Button("Play again", std::bind(&EndScreen::restartGame, this)))
{
	playAgainButton->setPosition({ 300.f, 600.f });
	displayPlayerScores();
}

EndScreen::~EndScreen()
{
	delete playAgainButton;
}

void EndScreen::renderScreen(sf::RenderWindow& window)
{
	GameScreen::renderScreen(window);
	players[0]->renderPlayer(window, Player::PlayerComponents::All);
	window.draw(*playAgainButton);
}

void EndScreen::updateScreen(sf::Time deltaTime)
{
	players[0]->updatePlayer(deltaTime, Player::PlayerComponents::All);
	playAgainButton->update(deltaTime);
}

void EndScreen::handleMouseClick(sf::Vector2f mousePosition)
{
	playAgainButton->handleMouseClick(mousePosition);
}

void EndScreen::displayPlayerScores()
{
	float playerListHeight = 100.f;
	float playerListIndent = 50.f;

	players[0]->centarTag(false);
	players[0]->playerTag.setRotation(0.f);
	players[0]->playerTag.setFillColor(sf::Color::Transparent);
	players[0]->playerTag.setPosition(playerListIndent, playerListHeight);
	players[0]->clickCount.setPosition(playerListIndent + 200.f, playerListHeight);

	players[0]->fadePlayer(true, Player::PlayerComponents::All);

}
void EndScreen::restartGame()
{
	stateManager->clearSettings();
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
}