#pragma once
#include <SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>

//Struct used to calculate prediction
struct PlayerMessage
{
	float x;
	float y;
	float timeSent;
};

class Server
{
public:
	void initialiseServer();
	void runTcpServer();
	void addMessage(PlayerMessage& msg);
	sf::Vector2f runPrediction(float gameTime);
	void update(float dt);
	void event();
	void windowDraw();

private:
	// Choose an arbitrary port for opening sockets
	const unsigned short port = 50001;
	// Create a server socket to accept new connections
	sf::TcpSocket socket;
	//Used to listen to a port
	sf::TcpListener listener;

	sf::RenderWindow window;

	sf::Event Event;

	//Player object creation
	sf::RectangleShape rectServer, rectClient, rectClientGhost;
	sf::Vector2f prevPosition, p2Position;
	int rectSpeed = 2.0f;

	std::vector<PlayerMessage> playerMessages;

	//Clock for timing the 'dt' value
	sf::Clock clock;
	float gameSpeed = 1.0f;
	float gameTime = 0.0f;
	float sentTime = 2.1f;

	bool updateBool = false;

};

