#include "UserInterface.h"

GUIComponent::GUIComponent()
{
}

GUIComponent::~GUIComponent()
{
}

sf::Font& GUIComponent::GUIFont = AssetManager::getInstance()->getFont("Beleren-Bold.ttf");
sf::Color GUIComponent::backgroundColor(0, 0, 0, 32);
sf::Color GUIComponent::outlineColor(255, 255, 255, 128);
sf::Color GUIComponent::activeOutlineColor(255, 255, 255, 226);

bool GUIComponent::isSelectable()
{
	return false;
}

void GUIComponent::update(sf::Time deltaTime)
{
}

bool GUIComponent::isClicked(sf::Vector2f mousePosition)
{
	return false;
}

bool GUIComponent::isClicked(sf::Vector2f mousePosition, const sf::Transform& parentTransform)
{
	return false;
}

void GUIComponent::handleMouseClick(sf::Vector2f mousePosition)
{
}

void GUIComponent::handleMouseClick(sf::Vector2f mousePosition, const sf::Transform& parentTransform)
{
}

void GUIComponent::handleTextEntry(sf::Event::TextEvent textEntry)
{
}

sf::Vector2f GUIComponent::getSize()
{
	return sf::Vector2f();
}
