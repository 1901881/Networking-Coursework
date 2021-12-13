#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

//struct PlayerMessage
//{
//	float x;
//	float y;
//	float timeSent;
//};

class Client
{
public:
	void initialiseClient();
	void runTcpClient();
	void createClientWindow();
	bool getWindowActive() { return windowActive; }
	void sendSocket(int x, int y);
	sf::Vector2f receiveSocket();

private:
	// Choose an arbitrary port for opening sockets
	const unsigned short port = 50001;

	sf::IpAddress server = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	sf::RenderWindow windowClient;
	bool windowActive = false;
	int rectSpeed = 2.0f;

	//std::vector<PlayerMessage> playerMessages;

};

