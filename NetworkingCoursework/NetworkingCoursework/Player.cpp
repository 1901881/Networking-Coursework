#include "Player.h"

int Player::playerCreate(sf::Color color)
{
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(20, 20));
	player.setFillColor(color);
	players.push_back(player);
	return playerIndex;
	playerIndex++;
}

void Player::playerSetPosition(sf::Vector2f position, int playerIndex)
{
	players[playerIndex].setPosition(position);
}

void Player::playerHandleInput(int playerIndex)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Move the Player to the right
		players[playerIndex].move(0.1f, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//Move the Player to the left
		players[playerIndex].move(-0.1f, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//Move the Player up
		players[playerIndex].move(0.0f, -0.1f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//Move the Player down
		players[playerIndex].move(0.0f, 0.1f);
	}
}
