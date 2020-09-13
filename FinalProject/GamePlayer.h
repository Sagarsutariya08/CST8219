#pragma once
#include "string"
#include <SFML/Graphics.hpp>
#include "ManageAssets.h"

class Player
{
public:
	Player(std::string name);
	~Player();

	enum PlayerComponents					// which part to operate on
	{
		Name,
		Score,
		All
	};

	void renderPlayer(sf::RenderWindow& window, PlayerComponents component);
	void updatePlayer(sf::Time deltaTime, PlayerComponents component);
	void fadePlayer(bool direction, PlayerComponents component);		// fade in (true), fade out (false)
	void pulsePlayer();

	void centarTag(bool center);
	std::string getName();
	void increaseClickScore();
	sf::Text playerTag;
	sf::Text clickCount;
	unsigned clickcount;
private:
	std::string name;
	static sf::Font& playerFont;
	static sf::Time animationTime;
};