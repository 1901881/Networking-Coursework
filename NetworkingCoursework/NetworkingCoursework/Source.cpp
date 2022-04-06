#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

using namespace std;

int main()
{
	sf::Clock deltaClock;
	float deltaTime;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Box Pusher");

	Game game(&window);


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		
		
		

		window.clear(sf::Color(18, 33, 43)); //Color Background

		//window.draw(scoreLine);
		//window.draw(player);

		window.display();
		}
		//Calculate delta time. How much time has passed
		//since it was last calculated (in seconds) and restart the clock.
		deltaTime = deltaClock.restart().asSeconds();

		game.update(deltaTime);
		game.render(deltaTime);
	}
	return 0;
}

