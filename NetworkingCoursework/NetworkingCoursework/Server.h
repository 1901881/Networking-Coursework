#pragma once
#include <SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>

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
	void createServerWindow();
	bool getWindowActive() { return windowActive; }
	void sendSocket(int prevX, int prevY, int rectX, int rectY, sf::Packet packet);
	void receiveSocket();
	void addMessage(PlayerMessage& msg);
	sf::Vector2f runPrediction(float gameTime);
	void push_front(PlayerMessage& msg);

private:
	// Choose an arbitrary port for opening sockets
	const unsigned short port = 50001;
	// Create a server socket to accept new connections
	sf::TcpListener listener;

	sf::TcpSocket socket;

	sf::RenderWindow window;
	bool windowActive = false;

	int rectSpeed = 2.0f;

	sf::RectangleShape rectServer, rectClient, rectClientGhost;

	std::vector<PlayerMessage> playerMessages;
};

