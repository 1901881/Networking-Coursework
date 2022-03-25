#include "BoxManager.h"

BoxManager::BoxManager(sf::RenderWindow* hwnd, sf::Vector2f position)
{
	window = hwnd;

	if (!boxTexture.loadFromFile("media/Box.png"))
	{
		// error...
	}
	boxTexture.setSmooth(true);
	boxSprite.setTexture(boxTexture);
	boxSprite.setScale(sf::Vector2f(0.35f, 0.35f));
	boxSprite.setOrigin(sf::Vector2f(boxTexture.getSize().x / 2.0f, boxTexture.getSize().y / 2.0f));
	boxSprite.setPosition(position);
}

BoxManager::~BoxManager()
{
}

void BoxManager::Update(float dt)
{
	boxSprite.move(velocity);
}


void BoxManager::Render()
{
	window->draw(boxSprite);
}
