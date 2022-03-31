#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class Player
{
public:
	Player(sf::RenderWindow* window, sf::Vector2f position, string textureName);
	~Player();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);
	void CheckCollision(float dt);
	void UpdateCollision(sf::FloatRect playerBounds, sf::FloatRect boxBounds);
	void PlayerMove(sf::Vector2f velocity) { playerSprite.move(velocity); }

	sf::Vector2f getVelocity() { return velocity; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	sf::Sprite getSprite() { return playerSprite; };
	sf::Vector2f getNewBoxPositionAddOn() { return newBoxPositionAddOn; };
	void setNewBoxPositionAddOn(sf::Vector2f newBoxPositionAddOn) { this->newBoxPositionAddOn = newBoxPositionAddOn; }


private:

	sf::RenderWindow* window;

	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	sf::Vector2f velocity;
	sf::Vector2f newBoxPositionAddOn = sf::Vector2f(0.0f, 0.0f);
	float boxSpeed = 1.0f;

	sf::FloatRect playerBounds;
	sf::FloatRect boxBounds;
	sf::FloatRect nextPos;

	float movementSpeed = 300.0f;
};


