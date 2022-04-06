#include "Player.h"

//loads player texture based on constructor parameter, initialises player sprite
Player::Player(sf::RenderWindow* window, sf::Vector2f position, string textureName, int ID)
{
	this->window = window;
	this->ID = ID;

	if (!playerTexture.loadFromFile(textureName))
	{
		cout << "Cannot load texture" << endl;
	}
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(sf::Vector2f(1.65f, 1.65f));
	playerSprite.setOrigin(sf::Vector2f(playerTexture.getSize().x / 2.0f, playerTexture.getSize().y / 2.0f));
	playerSprite.setPosition(position);

}

Player::~Player()
{
}

void Player::Update(float dt)
{
	HandleInput(dt);
	CheckCollision(dt);
}

void Player::Render()
{
	window->draw(playerSprite);
}

void Player::HandleInput(float dt)
{
	velocity = sf::Vector2f(0.0f, 0.0f);

	if(serverBool)
	{ 
	// Move player left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Ensure the line doesn't exceed the left bound
		if (playerSprite.getPosition().x > 10.0f + playerTexture.getSize().x / 2)
		{
			velocity.x = -movementSpeed * dt;
			angle = 180;
		}
	}

	// Move player right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Ensure the line doesn't exceed the right bound
		if (playerSprite.getPosition().x < window->getSize().x - playerTexture.getSize().x / 2)
		{
			velocity.x = movementSpeed * dt;
			angle = 0;
		}
	}

	// Move player up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// Ensure the line doesn't exceed the right bound
		if (playerSprite.getPosition().y > 0 + playerTexture.getSize().y / 2)
		{
			velocity.y = -movementSpeed * dt;
			angle = 270;
		}
	}

	// Move player down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// Ensure the line doesn't exceed the right bound
		if (playerSprite.getPosition().y < window->getSize().y - playerTexture.getSize().y / 2)
		{
			velocity.y = movementSpeed * dt;
			angle = 90;
		}
	}

	}

	if (clientBool)
	{
		// Move player left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// Ensure the line doesn't exceed the left bound
			if (playerSprite.getPosition().x > 10.0f + playerTexture.getSize().x / 2)
			{
				velocity.x = -movementSpeed * dt;
				angle = 180;
			}
		}

		// Move player right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// Ensure the line doesn't exceed the right bound
			if (playerSprite.getPosition().x < window->getSize().x - playerTexture.getSize().x / 2)
			{
				velocity.x = movementSpeed * dt;
				angle = 0;
			}
		}

		// Move player up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// Ensure the line doesn't exceed the right bound
			if (playerSprite.getPosition().y > 0 + playerTexture.getSize().y / 2)
			{
				velocity.y = -movementSpeed * dt;
				angle = 270;
			}
		}

		// Move player down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// Ensure the line doesn't exceed the right bound
			if (playerSprite.getPosition().y < window->getSize().y - playerTexture.getSize().y / 2)
			{
				velocity.y = movementSpeed * dt;
				angle = 90;
			}
		}

	}


}

void Player::CheckCollision(float dt)
{
	//Checks the player bounds against the box 
	//and moves the box based on which side is hit
	if (boxBounds.intersects(nextPos))
	{
		//Bottom Collision
		if (currentPlayerBounds.top < boxBounds.top
			&& currentPlayerBounds.top + currentPlayerBounds.height < boxBounds.top + boxBounds.height
			&& currentPlayerBounds.left < boxBounds.left + boxBounds.width
			&& currentPlayerBounds.left + currentPlayerBounds.width > boxBounds.left)
		{
			setVelocity(sf::Vector2f(getVelocity().y, 0.0f));
			newBoxPositionAddOn.y = boxSpeed;
			if (playerSprite.getRotation() == 270) {
				HandleInput(dt);
			}
		}
		//Top Collision
		if (currentPlayerBounds.top > boxBounds.top
			&& currentPlayerBounds.top + currentPlayerBounds.height > boxBounds.top + boxBounds.height
			&& currentPlayerBounds.left < boxBounds.left + boxBounds.width
			&& currentPlayerBounds.left + currentPlayerBounds.width > boxBounds.left)
		{
			setVelocity(sf::Vector2f(getVelocity().y, 0.0f));
			newBoxPositionAddOn.y = -boxSpeed;
			if (playerSprite.getRotation() == 90) {
				HandleInput(dt);
			}
		}
		//Right Collision
		if (currentPlayerBounds.left < boxBounds.left
			&& currentPlayerBounds.left + currentPlayerBounds.width < boxBounds.left + boxBounds.width
			&& currentPlayerBounds.top < boxBounds.top + boxBounds.height
			&& currentPlayerBounds.top + currentPlayerBounds.height > boxBounds.top)
		{
			setVelocity(sf::Vector2f(0.0f, getVelocity().y));
			newBoxPositionAddOn.x = boxSpeed;
			if (playerSprite.getRotation() == 180) {
				HandleInput(dt);
			}
		}
		//Left Collision
		if (currentPlayerBounds.left > boxBounds.left
			&& currentPlayerBounds.left + currentPlayerBounds.width > boxBounds.left + boxBounds.width
			&& currentPlayerBounds.top < boxBounds.top + boxBounds.height
			&& currentPlayerBounds.top + currentPlayerBounds.height > boxBounds.top)
		{
			setVelocity(sf::Vector2f(0.0f, getVelocity().y));
			newBoxPositionAddOn.x = -boxSpeed;
			if (playerSprite.getRotation() == 0) {
				HandleInput(dt);
			}
		}

	}

	if (externalPlayerBounds.intersects(nextPos))
	{
		//Bottom Collision
		if (currentPlayerBounds.top < externalPlayerBounds.top
			&& currentPlayerBounds.top + currentPlayerBounds.height < externalPlayerBounds.top + externalPlayerBounds.height
			&& currentPlayerBounds.left < externalPlayerBounds.left + externalPlayerBounds.width
			&& currentPlayerBounds.left + currentPlayerBounds.width > externalPlayerBounds.left)
		{
			setVelocity(sf::Vector2f(getVelocity().y, 0.0f));
			//newBoxPositionAddOn.y = boxSpeed;
			if (playerSprite.getRotation() == 270) {
				HandleInput(dt);
			}
		}
		//Top Collision
		if (currentPlayerBounds.top > externalPlayerBounds.top
			&& currentPlayerBounds.top + currentPlayerBounds.height > externalPlayerBounds.top + externalPlayerBounds.height
			&& currentPlayerBounds.left < externalPlayerBounds.left + externalPlayerBounds.width
			&& currentPlayerBounds.left + currentPlayerBounds.width > externalPlayerBounds.left)
		{
			setVelocity(sf::Vector2f(getVelocity().y, 0.0f));
			//newBoxPositionAddOn.y = -boxSpeed;
			if (playerSprite.getRotation() == 90) {
				HandleInput(dt);
			}
		}
		//Right Collision
		if (currentPlayerBounds.left < externalPlayerBounds.left
			&& currentPlayerBounds.left + currentPlayerBounds.width < externalPlayerBounds.left + externalPlayerBounds.width
			&& currentPlayerBounds.top < externalPlayerBounds.top + externalPlayerBounds.height
			&& currentPlayerBounds.top + currentPlayerBounds.height > externalPlayerBounds.top)
		{
			setVelocity(sf::Vector2f(0.0f, getVelocity().y));
			//newBoxPositionAddOn.x = boxSpeed;
			if (playerSprite.getRotation() == 180) {
				HandleInput(dt);
			}
		}
		//Left Collision
		if (currentPlayerBounds.left > externalPlayerBounds.left
			&& currentPlayerBounds.left + currentPlayerBounds.width > externalPlayerBounds.left + externalPlayerBounds.width
			&& currentPlayerBounds.top < externalPlayerBounds.top + externalPlayerBounds.height
			&& currentPlayerBounds.top + currentPlayerBounds.height > externalPlayerBounds.top)
		{
			setVelocity(sf::Vector2f(0.0f, getVelocity().y));
			//newBoxPositionAddOn.x = -boxSpeed;
			if (playerSprite.getRotation() == 0) {
				HandleInput(dt);
			}
		}

	}

}

void Player::UpdateCollision(sf::FloatRect currentPlayerBounds, sf::FloatRect externalPlayerBounds, sf::FloatRect boxBounds )
{
	//Collision
	//gets players next position
	nextPos = currentPlayerBounds;
	nextPos.left += getVelocity().x;
	nextPos.top += getVelocity().y;

	this->currentPlayerBounds = currentPlayerBounds;
	this->externalPlayerBounds = externalPlayerBounds;
	this->boxBounds = boxBounds;


}

//Fills packet with the box data and message type
sf::Packet Player::createPacket()
{
	sf::Packet packet;

	packet << static_cast<int>(getMessageType()) << getID() << getVelocity().x << getVelocity().y
		<< getAngle() << timeSent << getPosition().x
		<< getPosition().y << getNewBoxPositionAddOn().x << getNewBoxPositionAddOn().y 
		<< getClientPlayerBounds().top << getClientPlayerBounds().left << getClientPlayerBounds().width << getClientPlayerBounds().height;

	return packet;
}

