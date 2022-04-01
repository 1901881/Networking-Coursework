#include "ServerPlayer.h"

ServerPlayer::ServerPlayer(unsigned short port)
{
	runTcpServer(port);
}

ServerPlayer::~ServerPlayer()
{
}

void ServerPlayer::runTcpServer(unsigned short port)
{
	if (!clientConnected)
	{
		// Listen to the given port for incoming connections
		if (listener.listen(port) != sf::Socket::Done)
			return;
		std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;
		std::cout << "Server IP address: " << ip << std::endl;
		// Wait for a connection

		if (listener.accept(socket) != sf::Socket::Done)
			return;
		std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;
		clientConnected = true;
	}

	//// Send a message to the connected client
	//const char out[] = "Hi, I'm the server";
	//if (socket.send(out, sizeof(out)) != sf::Socket::Done)
	//	return;
	//std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

	//// Receive a message back from the client
	//char in[128];
	//std::size_t received;
	//if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
	//	return;
	//std::cout << "Answer received from the client: \"" << in << "\"" << std::endl;
}

/*
create player message

send player message

*/

void ServerPlayer::createPlayerMessage(int id, sf::Vector2f velocity, float angle)
{
	PlayerMessage serverPlayerMessage;
	serverPlayerMessage.id = id;
	serverPlayerMessage.velocityX = velocity.x;
	serverPlayerMessage.velocityY = velocity.y;
	serverPlayerMessage.angle = angle;
	sendPlayerMessage(serverPlayerMessage);
}

void ServerPlayer::sendPlayerMessage(PlayerMessage serverPlayerMessage)
{
	Packet packet;
	packet << serverPlayerMessage.id << serverPlayerMessage.velocityX << serverPlayerMessage.velocityY << serverPlayerMessage.angle;
	socket.send(packet);
}

void ServerPlayer::createBoxMessage(int id, sf::Vector2f velocity)
{
	BoxMessage boxMessage;
	boxMessage.id = id;
	boxMessage.velocityX = velocity.x;
	boxMessage.velocityY = velocity.y;
	sendBoxMessage(boxMessage);
}

void ServerPlayer::sendBoxMessage(BoxMessage boxMessage)
{
	Packet packet;
	packet << boxMessage.id << boxMessage.velocityX << boxMessage.velocityY;
	socket.send(packet);
}

/*
need to send player rotation 
then collision
see if player on client can go out of bounds and hit the boxes

*/