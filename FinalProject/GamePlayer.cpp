#include "GamePlayer.h"
#include<iostream>

using namespace std;
Player::Player(std::string name) :
	name(name),
	clickcount(0),
	playerTag(name, playerFont),
	clickCount("0", playerFont)
{
}

Player::~Player()
{
}

sf::Font& Player::playerFont = AssetManager::getInstance()->getFont("Beleren-Bold.ttf");
sf::Time Player::animationTime = sf::seconds(0.3f);

void Player::renderPlayer(sf::RenderWindow& window, PlayerComponents component)
{
	switch (component)
	{
	case PlayerComponents::Name:
		window.draw(playerTag);
		break;
	case PlayerComponents::Score:
		window.draw(playerTag);
		window.draw(clickCount);
		break;
	case PlayerComponents::All:
		window.draw(playerTag);
		window.draw(clickCount);
		break;
	default:
		break;
	}
}

void Player::updatePlayer(sf::Time deltaTime, PlayerComponents component)
{
	switch (component)
	{
	case PlayerComponents::Name:
		break;
	case PlayerComponents::Score:
		break;
	case PlayerComponents::All:
		break;
	default:
		break;
	}
}

void Player::fadePlayer(bool direction, PlayerComponents component)
{
	switch (component)
	{
	case PlayerComponents::Name:
		break;
	case PlayerComponents::Score:
		break;
	case PlayerComponents::All:
		break;
	default:
		break;
	}
}

void Player::pulsePlayer()
{
}

void Player::centarTag(bool center)
{
	if (center)
	{
		float playerWidth = playerTag.getLocalBounds().width;
		int playerHeight = playerTag.getCharacterSize();
		playerTag.setOrigin(playerWidth / 2.f, playerHeight / 2.f);
	}
	else
	{
		playerTag.setOrigin(0, 0);
	}
}

std::string Player::getName()
{
	return name;
}
void Player::increaseClickScore()
{
	clickcount++;
	clickCount.setString("Score: " + std::to_string(clickcount));
}