#include "Player.h"

Player::Player(sf::RenderWindow* window, sf::Vector2f position, string textureName)
{
	this->window = window;

	if (!playerTexture.loadFromFile(textureName))
	{
		// error...
		//"media/BoxPusher.png"

		cout << "Cannot load texture" << endl;
	}
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(sf::Vector2f(1.65f, 1.65f));
	playerSprite.setOrigin(sf::Vector2f(playerTexture.getSize().x / 2.0f, playerTexture.getSize().y / 2.0f));
	playerSprite.setPosition(position);


	/*
	
	*/
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	HandleInput(dt);
	CheckCollision(dt);
	//playerSprite.move(velocity);

	/*
	changes:
	velocity
	rotation
	newBoxPositionAddon
	*/
}

void Player::Render()
{
	window->draw(playerSprite);
}

void Player::HandleInput(float dt)
{
	velocity = sf::Vector2f(0.0f, 0.0f);

	// Move player left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Ensure the line doesn't exceed the left bound
		if (playerSprite.getPosition().x > 10.0f + playerTexture.getSize().x / 2)
		{
			velocity.x = -movementSpeed * dt;
			//playerSprite.setRotation(180);
			angle = 180;
		}
	}

	// Move player right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Ensure the line doesn't exceed the right bound
		if (playerSprite.getPosition().x < window->getSize().x - playerTexture.getSize().x / 2)
		{
			// Move the line 1 unit right
			velocity.x = movementSpeed * dt;
			//playerSprite.setRotation(0);
			angle = 0;
		}
	}

	// Move player up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// Ensure the line doesn't exceed the right bound
		if (playerSprite.getPosition().y > 0 + playerTexture.getSize().y / 2)
		{
			// Move the line 1 unit right
			velocity.y = -movementSpeed * dt;
			//playerSprite.setRotation(270);
			angle = 270;
		}
	}

	// Move player down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// Ensure the line doesn't exceed the right bound
		if (playerSprite.getPosition().y < window->getSize().y - playerTexture.getSize().y / 2)
		{
			// Move the line 1 unit right
			velocity.y = movementSpeed * dt;
			//playerSprite.setRotation(90);
			angle = 90;
		}
	}


}

void Player::CheckCollision(float dt)
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
			if (playerSprite.getRotation() == 270) {
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
			if (playerSprite.getRotation() == 90) {
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
			if (playerSprite.getRotation() == 180) {
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
			if (playerSprite.getRotation() == 0) {
				HandleInput(dt);
			}
		}

	}
}

void Player::UpdateCollision(sf::FloatRect playerBounds, sf::FloatRect boxBounds)
{
	//Collision
	//get players next position
	nextPos = playerBounds;
	nextPos.left += getVelocity().x;
	nextPos.top += getVelocity().y;

	this->playerBounds = playerBounds;
	this->boxBounds = boxBounds;


}