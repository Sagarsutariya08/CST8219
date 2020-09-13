#include "SetTimeout.h"

SetTimeout::SetTimeout() :
	delaying(false),
	elapsedTime(sf::Time::Zero)
{
}

SetTimeout::~SetTimeout()
{
}

void SetTimeout::startTimeout(sf::Time timeoutTime, std::function<void(void)> timeoutCallback)
{
	delaying = true;
	timeout = timeoutTime;
	callback = timeoutCallback;
}

void SetTimeout::clearTimeout(bool fireCallback)
{
	if (fireCallback)
	{
		callback();
	}
	delaying = false;
	elapsedTime = sf::Time::Zero;
	timeout = sf::Time::Zero;
	callback = nullptr;
}

void SetTimeout::update(sf::Time deltaTime)
{
	if (!delaying)
	{
		return;
	}
	elapsedTime += deltaTime;
	if (elapsedTime >= timeout)
	{
		clearTimeout(true);
		return;
	}
}