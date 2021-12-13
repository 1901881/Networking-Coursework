#pragma once
#include<SFML/Graphics.hpp>
#include <vector>

class Player
{
public:

	int playerCreate(sf::Color color);
	void playerSetPosition(sf::Vector2f position, int playerIndex);
	void playerHandleInput(int playerIndex);
	void playerRender(sf::RenderWindow window, int playerIndex);
	sf::RectangleShape playerGet(int playerIndex) { return players[playerIndex]; }

private:

	std::vector< sf::RectangleShape> players;
	int playerIndex = 0;
};

