#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Client
{
public:
	void initialiseClient();
	void runTcpClient();
	void windowDraw();
	void updateClient(float dt);
	void event();

private:


	//gets the local ipaddress so that it can connect to socket using the port
	sf::IpAddress server = sf::IpAddress::getLocalAddress();
	// Choose an arbitrary port for opening sockets
	const unsigned short port = 50001;

	sf::TcpSocket socket;
	sf::RenderWindow windowClient;

	sf::RectangleShape rectServer, rectClient;
	sf::Vector2f prevPosition, p2Position;

	int rectSpeed = 2.0f;

	//Clock for timing the 'dt' value
	sf::Clock clock;
	float gameSpeed = 1.0f;
	float gameTime = 0.0f;
	float timer = 0.0f;

	bool update = false;
	sf::Event Event;

};

