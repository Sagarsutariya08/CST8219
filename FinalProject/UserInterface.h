#pragma once
#include <SFML/Graphics.hpp>
#include "ManageAssets.h"

class GUIComponent : public sf::Drawable, public sf::Transformable
{
public:
	GUIComponent();
	~GUIComponent();

	virtual bool isSelectable() = 0;
	virtual void update(sf::Time deltaTime);
	virtual bool isClicked(sf::Vector2f mousePosition);
	virtual bool isClicked(sf::Vector2f mousePosition, const sf::Transform& parentTransform);
	virtual void handleMouseClick(sf::Vector2f mousePosition);
	virtual void handleMouseClick(sf::Vector2f mousePosition, const sf::Transform& parentTransform);
	virtual void handleTextEntry(sf::Event::TextEvent textEntry);
	virtual sf::Vector2f getSize();
protected:
	static sf::Font& GUIFont;
	static sf::Color backgroundColor;
	static sf::Color outlineColor;
	static sf::Color activeOutlineColor;
};