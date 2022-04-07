#include "BoxManager.h"

//loads box texture, initialises box sprite
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
}


void BoxManager::Render()
{
	window->draw(boxSprite);
}

//Fills packet with the box data and message type
sf::Packet BoxManager::createPacket()
{
	sf::Packet packet;

	packet << static_cast<int>(getMessageType()) << getID() << getVelocity().x << getVelocity().y
		<< getPosition().x << getPosition().y;

	return packet;
}
