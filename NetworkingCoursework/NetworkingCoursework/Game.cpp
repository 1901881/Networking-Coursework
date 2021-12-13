#include "Game.h"

void Game::setupTCPServer()
{
	serverObj.initialiseServer();
	serverPlayerID = playerObj.playerCreate(sf::Color::Red);
	playerObj.playerSetPosition(sf::Vector2f(10, 10), serverPlayerID);
}

void Game::setupTCPClient()
{
	clientObj.initialiseClient();
	clientPlayerID = playerObj.playerCreate(sf::Color::Green);
	playerObj.playerSetPosition(sf::Vector2f(20, 0), clientPlayerID);
}

void Game::runGame()
{
	clientPlayerID = playerObj.playerCreate(sf::Color::Green);
	playerObj.playerSetPosition(sf::Vector2f(20, 0), clientPlayerID);

	serverWindow.create(sf::VideoMode(800, 600, 32), "Server Window");
	clientWindow.create(sf::VideoMode(800, 600, 32), "Client Window");

	while (clientWindow.isOpen() && serverWindow.isOpen())
	{
		//Get the time since the last frame in milliseconds
		//float dt = clock.restart().asSeconds() * gameSpeed;

		sf::Event Event;
		while (clientWindow.pollEvent(Event) && serverWindow.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
			{
				serverWindow.close();
				clientWindow.close();
			}
			else if (Event.type == sf::Event::GainedFocus)
			{
				updateWindow = true;
			}
			else if (Event.type == sf::Event::LostFocus)
			{
				updateWindow = false;
			}
		}

		sf::Vector2f prevPosition = sf::Vector2f(playerObj.playerGet(clientPlayerID).getPosition().x, playerObj.playerGet(clientPlayerID).getPosition().y);

		if (updateWindow)
		{
			//upate date players
			playerObj.playerHandleInput(clientPlayerID);


			//send player data


			//render players
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(20, 20));
			rect.setFillColor(sf::Color::Green);
			rect.setPosition(sf::Vector2f(20, 0));


			clientWindow.draw(playerObj.playerGet(clientPlayerID));
			serverWindow.draw(playerObj.playerGet(serverPlayerID));
			//clientWindow.draw(rect);
		}



		sf::Packet packet;
		//Checks if the player has moved if yes the new position data is sent
		if (prevPosition.x != playerObj.playerGet(clientPlayerID).getPosition().x || prevPosition.y != playerObj.playerGet(clientPlayerID).getPosition().y)
		{
			clientObj.sendSocket(playerObj.playerGet(clientPlayerID).getPosition().x, playerObj.playerGet(clientPlayerID).getPosition().y);
		}
		
		playerObj.playerSetPosition(sf::Vector2f(20,20), serverPlayerID);


		
		clientWindow.display();
		clientWindow.clear();

		serverWindow.display();
		serverWindow.clear();
	}
	system("pause");
}
