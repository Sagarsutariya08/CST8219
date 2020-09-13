#pragma once
#include <functional>
#include "UserInterface.h"
#include "ManageAssets.h"
#include "SetTimeout.h"

class Button : public GUIComponent
{
public:
	Button(std::string btnText, std::function<void()> callback);
	~Button();

	virtual bool isSelectable();
	virtual void update(sf::Time deltaTime);
	virtual bool isClicked(sf::Vector2f mousePosition);
	virtual bool isClicked(sf::Vector2f mousePosition, const sf::Transform& parentTransform);
	virtual void handleMouseClick(sf::Vector2f mousePosition);
	virtual void handleMouseClick(sf::Vector2f mousePosition, const sf::Transform& parentTransform);
	virtual sf::Vector2f getSize();
private:
	static sf::Sound buttonSound;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::function<void()> callback;

	sf::RectangleShape shape;
	sf::Text text;

	SetTimeout* timeout;
	void toggleActive();
	bool active;
};