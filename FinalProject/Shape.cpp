#include "Shape.h"

Card::Card(unsigned id, Card::Suit suit) :
	id(id),
	cardSuit(suit),
	cardSprite(cardBackTexture)
{
	setCardTexture(suit);
	cardAnimation = new CardAnimation(&cardSprite, animationTime, &cardTexture);
}

Card::~Card()
{
	delete cardAnimation;
}

sf::Texture& Card::cardBackTexture = AssetManager::getInstance()->getTexture("FrontCover.png");
sf::Vector2u Card::size = cardBackTexture.getSize();
sf::Sound Card::cardSound(AssetManager::getInstance()->getSoundBuffer("CardTurnSound.wav"));

sf::Time Card::animationTime = sf::seconds(0.5f);

void Card::renderCard(sf::RenderWindow& window)
{
	window.draw(cardSprite);
}

void Card::updateCard(sf::Time deltaTime)
{
	cardAnimation->updateAnimated(deltaTime);
}

void Card::setPosition(sf::Vector2u deckPosition)
{
	cardSprite.setOrigin(float(size.x / 2), float(size.y / 2)); // set origin to center of card
	sf::Vector2f position;
	position.x = deckPosition.x * size.x + 10.f * deckPosition.x + size.x / 2;  // position of card + origin offset + margin
	position.y = deckPosition.y * size.y + 10.f * deckPosition.y + size.y / 2;
	cardSprite.setPosition(position);
}

bool Card::isCardClicked(sf::Vector2f mousePosition)
{
	if (cardAnimation->isPlaying())
	{
		return false;
	}
	return cardSprite.getGlobalBounds().contains(mousePosition);
}

void Card::flipCard()
{
	cardAnimation->startAnimation();
	cardSound.play();
}

Card::Suit Card::getSuit()
{
	return cardSuit;
}

sf::Vector2u Card::getSize()
{
	return size;
}

void Card::setCardTexture(Suit suit)
{
	std::string filename;
	switch (suit)
	{
	case Card::Triangle:
		filename = "Triangle.png";
		break;
	case Card::Pentagon:
		filename = "Pentagon.png";
		break;
	case Card::Rectangle:
		filename = "Rectangle.png";
		break;
	case Card::Circle:
		filename = "Circle.png";
		break;
	case Card::Hexagon:
		filename = "Hexagon.png";
		break;
	case Card::Star:
		filename = "Star.png";
		break;
	case Card::Ellipse:
		filename = "Ellipse.png";
		break;
	case Card::Square:
		filename = "Square.png";
		break;
	case Card::Up:
		filename = "Up.png";
		break;
	case Card::Down:
		filename = "Down.png";
		break;
	default:
		break;
	}

	cardTexture = AssetManager::getInstance()->getTexture(filename);
}
