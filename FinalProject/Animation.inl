#include "Animation.h"



template <typename Animated>
Animation<Animated>::Animation() :
	elapsedTime(sf::Time::Zero),
	playing(false)
{
}

template <typename Animated>
Animation<Animated>::Animation(Animated* animated, sf::Time animationDuration) :
	animated(animated),
	animationDuration(animationDuration),
	elapsedTime(sf::Time::Zero),
	playing(false)
{
}

template <typename Animated>
Animation<Animated>::~Animation()
{
}

template <typename Animated>
const double Animation<Animated>::pi = std::acos(-1);

template <typename Animated>
void Animation<Animated>::startAnimation()
{
	if (!playing)
	{
		playing = true;
	}
}

template <typename Animated>
void Animation<Animated>::stopAnimation()
{
	playing = false;
	elapsedTime = sf::Time::Zero;
}

template <typename Animated>
void Animation<Animated>::updateAnimated(sf::Time deltaTime)
{
	if (!playing)
	{
		return;
	}
	elapsedTime += deltaTime;
	if (elapsedTime >= animationDuration)
	{
		stopAnimation();
		return;
	}

	applyTransformation();
}

template<typename Animated>
inline bool Animation<Animated>::isPlaying()
{
	return playing;
}
