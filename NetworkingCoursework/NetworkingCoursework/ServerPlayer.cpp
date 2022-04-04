#include "ServerPlayer.h"

ServerPlayer::ServerPlayer(unsigned short port)
{
	runNetwork(port);
}

ServerPlayer::~ServerPlayer()
{
}

void ServerPlayer::runNetwork(unsigned short port)
{
	//socket.setBlocking(false);

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

void ServerPlayer::receivePacket()
{
	extern NetworkMessages networkMessagesContainer;

	BaseMessage baseMessage;

	sf::Packet packet;
	socket.receive(packet);


	if (packet >> baseMessage.encodedMessageType)
	{
		MessageType messageType = networkMessagesContainer.decodeMessageType(baseMessage.encodedMessageType);

		switch (messageType)
		{
		case MessageType::Player:
			receivePlayerPacket(packet);
			break;
		case MessageType::Box:
			receiveBoxPacket(packet);
			break;
		case MessageType::Score:
			receiveScorePacket(packet);
			break;
		case MessageType::Invalid:
			std::cout << "Received Message Invalid" << std::endl;
			// std::cout << baseMessage.encodedMessageType << std::endl;
			 //std::cout << messageType << std::endl;
			break;
		}
	}
}

void ServerPlayer::sendMessage(ObjectInterface* object)
{
	//sf::TcpSocket newSocket = socket;
	sf::Packet packet;

	
	switch (object->getObjectType()) 
	{
	case ObjectType::Player:
		// fill packet with data
		packet << static_cast<int>(object->getMessageType()) << object->getID() << object->getVelocity().x << object->getVelocity().y
			<< object->getAngle() << object->getTimeSent() << object->getPosition().x
			<< object->getPosition().y;
		break;
	case ObjectType::Box:
		// code block
		break;
	default:
		//cout broke
		break;
	}

	//sf::Packet packet = object->createPacket();
	socket.send(packet);
}

void ServerPlayer::receivePlayerPacket(sf::Packet packet)
{
	extern NetworkMessages networkMessagesContainer;
	PlayerMessage playerMessage;
	if (packet >> playerMessage.id >> playerMessage.velocityX >> playerMessage.velocityY >> playerMessage.angle >> playerMessage.timeSent >> playerMessage.position.x >> playerMessage.position.y)
	{
		//update server player infor on client side
		//std::cout << "player velocity x " << playerMessage.velocityX << std::endl;
	   // serverPlayerVelocity = sf::Vector2f(playerMessage.velocityX, playerMessage.velocityY);
		//std::cout << "Client cpp: " << playerMessage.angle << std::endl;
		//NetworkContainer::playerMessage = playerMessage;
		networkMessagesContainer.setPlayerMessage(playerMessage);
	}
}

void ServerPlayer::receiveBoxPacket(sf::Packet packet)
{
	extern NetworkMessages networkMessagesContainer;
	BoxMessage boxMessage;

	if (packet >> boxMessage.id >> boxMessage.velocityX >> boxMessage.velocityY >> boxMessage.position.x >> boxMessage.position.y)
	{
		//update server player infor on client side
		//std::cout << "player velocity x " << playerMessage.velocityX << std::endl;
		//serverPlayerVelocity = sf::Vector2f(playerMessage.velocityX, playerMessage.velocityY);
		//std::cout << "Client cpp: " << playerMessage.angle << std::endl;
		//NetworkContainer::boxMessage = boxMessage;
		networkMessagesContainer.setBoxMessage(boxMessage);
	}
}

void ServerPlayer::receiveScorePacket(sf::Packet packet)
{
	extern NetworkMessages networkMessagesContainer;
	ScoreMessage scoreMessage;

	if (packet >> scoreMessage.scoreLeft >> scoreMessage.scoreRight)
	{
		//NetworkContainer::scoreMessage = scoreMessage;
		networkMessagesContainer.setScoreMessage(scoreMessage);
	}
}
