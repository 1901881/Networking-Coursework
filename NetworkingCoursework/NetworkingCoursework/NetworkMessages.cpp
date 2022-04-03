#include "NetworkMessages.h"

void receivePacket(sf::TcpSocket socket)
{
    BaseMessage baseMessage;

    sf::Packet packet;
    socket.receive(packet);


    if (packet >> baseMessage.encodedMessageType)
    {
        MessageType messageType = decodeMessageType(baseMessage.encodedMessageType);

        switch (messageType)
        {
        case MessageType::Player:
            receivePlayerPacket(packet);
        case MessageType::Box:
            receiveBoxPacket(packet);
        case MessageType::Score:
            receiveScorePacket(packet);
        case MessageType::Invalid:
            std::cout << "Received Message Invalid" << std::endl;
        }

    }
}

void receivePlayerPacket(sf::Packet packet)
{
    PlayerMessage playerMessage;
    if (packet >> playerMessage.id >> playerMessage.velocityX >> playerMessage.velocityY >> playerMessage.angle >> playerMessage.timeSent >> playerMessage.position.x >> playerMessage.position.y)
    {
        //update server player infor on client side
        //std::cout << "player velocity x " << playerMessage.velocityX << std::endl;
       // serverPlayerVelocity = sf::Vector2f(playerMessage.velocityX, playerMessage.velocityY);
        //std::cout << "Client cpp: " << playerMessage.angle << std::endl;
        NetworkContainer::playerMessage = playerMessage;
    }
}

void receiveBoxPacket(sf::Packet packet)
{
    BoxMessage boxMessage;

    if (packet >> boxMessage.id >> boxMessage.velocityX >> boxMessage.velocityY >> boxMessage.position.x >> boxMessage.position.y)
    {
        //update server player infor on client side
        //std::cout << "player velocity x " << playerMessage.velocityX << std::endl;
        //serverPlayerVelocity = sf::Vector2f(playerMessage.velocityX, playerMessage.velocityY);
        //std::cout << "Client cpp: " << playerMessage.angle << std::endl;
        NetworkContainer::boxMessage = boxMessage;
    }
}

void receiveScorePacket(sf::Packet packet)
{
    ScoreMessage scoreMessage;

    if (packet >> scoreMessage.scoreLeft >> scoreMessage.scoreRight)
    {
        NetworkContainer::scoreMessage = scoreMessage;
    }
}

void sendMessage(sf::TcpSocket socket, ObjectInterface* object)
{
    //sf::TcpSocket newSocket = socket;
    sf::Packet packet = object->createPacket();
    socket.send(packet);
}




