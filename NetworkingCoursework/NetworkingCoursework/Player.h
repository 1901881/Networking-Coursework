#pragma once
#include<SFML/Graphics.hpp>
#include <vector>

class Player
{
public:

	int playerCreate(sf::Color color);
	void playerSetPosition(sf::Vector2f position, int playerIndex);
	void playerHandleInput(int playerIndex);
	sf::RectangleShape playerGet(int playerIndex) { return players[playerIndex]; }
	sf::Vector2f playerGetPosition(int playerIndex) { return players[playerIndex].getPosition(); }

private:

	std::vector< sf::RectangleShape> players;
	int playerIndex = 0;
};

