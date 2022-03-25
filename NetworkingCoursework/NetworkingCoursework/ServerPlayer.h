#pragma once

#include <SFML/Graphics.hpp>

class ServerPlayer
{
public:
	ServerPlayer(sf::RenderWindow* hwnd);
	~ServerPlayer();

	void Update(float dt);
	void HandleInput(float dt);
	void Render();
	sf::Sprite getSprite() { return serverPlayerSprite; };
	sf::Vector2f getVelocity() { return velocity; };
	sf::Vector2f getNewBoxPositionAddOn() { return newBoxPositionAddOn; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	void setNewBoxPositionAddOn(sf::Vector2f newBoxPositionAddOn) { this->newBoxPositionAddOn = newBoxPositionAddOn; }
	void setMovementSpeed(float movementSpeed) { this->movementSpeed = movementSpeed; }
	void CheckCollision(float dt);
	void UpdateCollision(sf::FloatRect playerBounds, sf::FloatRect boxBounds);
private:
	sf::RenderWindow* window;

	sf::Sprite serverPlayerSprite;
	sf::Texture serverPlayerTexture;

	sf::Vector2f velocity;
	sf::Vector2f newBoxPositionAddOn = sf::Vector2f(0.0f, 0.0f);
	float boxSpeed = 1.0f;

	sf::FloatRect playerBounds;
	sf::FloatRect boxBounds;
	sf::FloatRect nextPos;

	float movementSpeed = 300.0f;

};

