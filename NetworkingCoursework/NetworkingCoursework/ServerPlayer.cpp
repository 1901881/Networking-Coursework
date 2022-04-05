#include "ServerPlayer.h"

ServerPlayer::ServerPlayer(unsigned short port)
{
	runNetwork(port);

	//maybe change this to nand
	for (int x = 0; x < 3; x++)
	{
		PlayerMessage p;
		p.velocityX = -2000;//arbitrary values used for testing 
		p.velocityY = -2000;
		p.angle = -2000;
		p.id = -2000;
		p.position.x = -2000;
		p.position.y = -2000;
		clientPlayerMessageVector.push_back(p);
	}
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
	//std::cout << "Message sent to the client: \""  << out << "\"" << std::endl;

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
		packet = object->createPacket();
		break;
	case ObjectType::Box:
		// code block
		packet = object->createPacket();
		break;
	case ObjectType::Score:
		// code block
		packet = object->createPacket();
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
	if (packet >> playerMessage.id >> playerMessage.velocityX >> playerMessage.velocityY >> playerMessage.angle >> playerMessage.timeSent >> playerMessage.position.x >> playerMessage.position.y >> playerMessage.newBoxPositionAddOn.x >> playerMessage.newBoxPositionAddOn.y)
	{
		//update server player infor on client side
		//std::cout << "player velocity x " << playerMessage.velocityX << std::endl;
	   // serverPlayerVelocity = sf::Vector2f(playerMessage.velocityX, playerMessage.velocityY);
		//std::cout << "Client cpp: " << playerMessage.angle << std::endl;
		//NetworkContainer::playerMessage = playerMessage;
		networkMessagesContainer.setPlayerMessage(playerMessage);
		clientPlayerMessageVector.push_back(playerMessage);
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

void ServerPlayer::addClientPlayerMessage(PlayerMessage& msg)
{
	//when a new message is sent it shuffles all the other messages into the next slot in memory
	clientPlayerMessageVector[2] = clientPlayerMessageVector[1];
	clientPlayerMessageVector[1] = clientPlayerMessageVector[0];
	clientPlayerMessageVector[0] = msg;
}

sf::Vector2f ServerPlayer::runPrediction(float dt)
{
	extern NetworkMessages networkMessagesContainer;
	const int msize = clientPlayerMessageVector.size();

	//waits until the vector is filled with the client sides data before running prediction
	if (clientPlayerMessageVector[2].position.x == -2000)
	{
		//return sf::Vector2f(serverPlayerMessage.position.x, serverPlayerMessage.position.y);
		return sf::Vector2f(networkMessagesContainer.getPlayerMessage().position);
	}
	int msg0Size = msize - 1;
	int msg1Size = msize - 2;
	int msg2Size = msize - 3;
	const PlayerMessage& msg0 = clientPlayerMessageVector[msg0Size];
	const PlayerMessage& msg1 = clientPlayerMessageVector[msg1Size];
	const PlayerMessage& msg2 = clientPlayerMessageVector[msg2Size];

	//Linear
	//Next position = previous position + displacement
	//displacement = speed*time
	//speed = distance between last two position / time between last two positions

	float speed = ((msg0.position.x - msg1.position.x) - (msg0.position.y - msg1.position.y)) / (msg0.timeSent - msg1.timeSent);
	float displacement = speed * (dt - msg0.timeSent);
	float nextPositionX = msg0.position.x + displacement;
	float nextPositionY = msg0.position.y + displacement;
	return sf::Vector2f(nextPositionX, nextPositionY);
	//return sf::Vector2f(1, 1);

	////add latency

	///*
	//need to get liner prediction calculation

	//need delta time and time sent

	//save velocity when sent

	//ignore null references

	//set as predictid velocity
	//then use that in game to move player.

	//////////////////////////////////////////

	//need to run it off position
	//*/
}
