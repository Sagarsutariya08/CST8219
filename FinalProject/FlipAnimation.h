#pragma once
#include "Animation.h"


class CardAnimation :
	public Animation<sf::Sprite>
{
public:
	CardAnimation();
	CardAnimation(sf::Sprite* animated, sf::Time animationDuration, sf::Texture* cardTexture);
	~CardAnimation();

	void stopAnimation();
private:
	virtual void applyTransformation();
	bool isFlipped;
	void toggleTexture();
	const sf::Texture* cardTexture;
	const sf::Texture* cardBackTexture;
};
