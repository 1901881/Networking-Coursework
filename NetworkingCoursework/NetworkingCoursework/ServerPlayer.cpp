#include "ServerPlayer.h"

ServerPlayer::ServerPlayer(sf::RenderWindow* hwnd)
{
	window = hwnd;

	if (!serverPlayerTexture.loadFromFile("media/BoxPusher.png"))
	{
		// error...
	}
	serverPlayerTexture.setSmooth(true);
	serverPlayerSprite.setTexture(serverPlayerTexture);
	serverPlayerSprite.setScale(sf::Vector2f(1.65f, 1.65f));
	serverPlayerSprite.setOrigin(sf::Vector2f(serverPlayerTexture.getSize().x / 2.0f, serverPlayerTexture.getSize().y / 2.0f));
	serverPlayerSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 1.5f);
}

ServerPlayer::~ServerPlayer()
{
}

void ServerPlayer::Update(float dt)
{
	HandleInput(dt);
	CheckCollision(dt);
	serverPlayerSprite.move(velocity);
}


void ServerPlayer::HandleInput(float dt)
{
	velocity = sf::Vector2f(0.0f, 0.0f);

	// Move player left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Ensure the line doesn't exceed the left bound
		if (serverPlayerSprite.getPosition().x > 10.0f + serverPlayerTexture.getSize().x / 2)
		{
			velocity.x = -movementSpeed * dt;
			serverPlayerSprite.setRotation(180);
		}
	}

	// Move player right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Ensure the line doesn't exceed the right bound
		if (serverPlayerSprite.getPosition().x < window->getSize().x - serverPlayerTexture.getSize().x / 2)
		{
			// Move the line 1 unit right
			velocity.x = movementSpeed * dt;
			serverPlayerSprite.setRotation(0);
		}
	}

	// Move player up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// Ensure the line doesn't exceed the right bound
		if (serverPlayerSprite.getPosition().y > 0 + serverPlayerTexture.getSize().y / 2)
		{
			// Move the line 1 unit right
			velocity.y = -movementSpeed * dt;
			serverPlayerSprite.setRotation(270);
		}
	}

	// Move player down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// Ensure the line doesn't exceed the right bound
		if (serverPlayerSprite.getPosition().y < window->getSize().y - serverPlayerTexture.getSize().y / 2)
		{
			// Move the line 1 unit right
			velocity.y = movementSpeed * dt;
			serverPlayerSprite.setRotation(90);
		}
	}

	//checkCollision();

	
}

void ServerPlayer::Render()
{
	window->draw(serverPlayerSprite);
}

void ServerPlayer::CheckCollision(float dt)
{

	if (boxBounds.intersects(nextPos))
	{
			//Bottom Collision
			if (playerBounds.top < boxBounds.top
				&& playerBounds.top + playerBounds.height < boxBounds.top + boxBounds.height
				&& playerBounds.left < boxBounds.left + boxBounds.width
				&& playerBounds.left + playerBounds.width > boxBounds.left)
			{
				setVelocity(sf::Vector2f(getVelocity().y, 0.0f));
				newBoxPositionAddOn.y = boxSpeed;
				if (serverPlayerSprite.getRotation() == 270) {
					HandleInput(dt);
				}
			}
			//Top Collision
			if (playerBounds.top > boxBounds.top
				&& playerBounds.top + playerBounds.height > boxBounds.top + boxBounds.height
				&& playerBounds.left < boxBounds.left + boxBounds.width
				&& playerBounds.left + playerBounds.width > boxBounds.left)
			{
				setVelocity(sf::Vector2f(getVelocity().y, 0.0f));
				newBoxPositionAddOn.y = -boxSpeed;
				if (serverPlayerSprite.getRotation() == 90) {
					HandleInput(dt);
				}
			}
			//Right Collision
			if (playerBounds.left < boxBounds.left
				&& playerBounds.left + playerBounds.width < boxBounds.left + boxBounds.width
				&& playerBounds.top < boxBounds.top + boxBounds.height
				&& playerBounds.top + playerBounds.height > boxBounds.top)
			{
				setVelocity(sf::Vector2f(0.0f, getVelocity().y));
				newBoxPositionAddOn.x = boxSpeed;
				//serverPlayerSprite.setPosition(playerBounds.left, boxBounds.top + boxBounds.height);
				if (serverPlayerSprite.getRotation() == 180) {
					HandleInput(dt);
				}
			}
			//Left Collision
			if (playerBounds.left > boxBounds.left
				&& playerBounds.left + playerBounds.width > boxBounds.left + boxBounds.width
				&& playerBounds.top < boxBounds.top + boxBounds.height
				&& playerBounds.top + playerBounds.height > boxBounds.top)
			{
				setVelocity(sf::Vector2f(0.0f, getVelocity().y));
				newBoxPositionAddOn.x = -boxSpeed;
				if (serverPlayerSprite.getRotation() == 0) {
					HandleInput(dt);
				}
			}

	}
}

void ServerPlayer::UpdateCollision(sf::FloatRect playerBounds, sf::FloatRect boxBounds)
{
	//Collision
	//get players next position
	nextPos = playerBounds;
	nextPos.left += getVelocity().x;
	nextPos.top += getVelocity().y;

	this->playerBounds = playerBounds;
	this->boxBounds = boxBounds;


}