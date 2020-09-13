#pragma once
#include <functional>
#include "SFML/System.hpp"

class SetTimeout
{
public:
	SetTimeout();
	~SetTimeout();

	void startTimeout(sf::Time timeoutTime, std::function<void(void)> timeoutCallback);
	void clearTimeout(bool fireCallback);
	void update(sf::Time deltaTime);
	bool delaying;
private:
	sf::Time elapsedTime;
	sf::Time timeout;
	std::function<void()> callback;
};