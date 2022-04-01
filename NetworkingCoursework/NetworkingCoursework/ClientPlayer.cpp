#include "ClientPlayer.h"

ClientPlayer::ClientPlayer(unsigned short port)
{
    runTcpClient(port);
}

ClientPlayer::~ClientPlayer()
{
}

void ClientPlayer::runTcpClient(unsigned short port)
{
    // Ask for the server address

    do
    {
        std::cout << "Type the ip address of the server to connect to: ";
        std::cin >> server;
    } while (server == sf::IpAddress::None);


    // Connect to the server
    if (socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

    //// Receive a message from the server
    //char in[128];
    //std::size_t received;
    //if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
    //    return;
    //std::cout << "Message received from the server: \"" << in << "\"" << std::endl;

    //// Send an answer to the server
    //const char out[] = "Hi, I'm a client";
    //if (socket.send(out, sizeof(out)) != sf::Socket::Done)
    //    return;
    //std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
}

void ClientPlayer::receivePlayerMessage()
{
    PlayerMessage serverPlayerMessage;
    Packet packet;
    socket.receive(packet);
    if (packet >> serverPlayerMessage.id >> serverPlayerMessage.velocityX >> serverPlayerMessage.velocityY >> serverPlayerMessage.angle)
    {
     	//update server player infor on client side
        //std::cout << "player velocity x " << serverPlayerMessage.velocityX << std::endl;
     	serverPlayerVelocity = sf::Vector2f(serverPlayerMessage.velocityX, serverPlayerMessage.velocityY);
        //std::cout << "Client cpp: " << serverPlayerMessage.angle << std::endl;
        this->serverPlayerMessage = serverPlayerMessage;
    }
}

void ClientPlayer::receiveBoxMessage()
{
    BoxMessage boxMessage;
    Packet packet;
    socket.receive(packet);
    if (packet >> boxMessage.id >> boxMessage.velocityX >> boxMessage.velocityY)
    {
        //update server player infor on client side
        //std::cout << "player velocity x " << serverPlayerMessage.velocityX << std::endl;
        //serverPlayerVelocity = sf::Vector2f(serverPlayerMessage.velocityX, serverPlayerMessage.velocityY);
        //std::cout << "Client cpp: " << serverPlayerMessage.angle << std::endl;
        this->boxMessage = boxMessage;
    }
}

/*
receive message

then get infoe and place it in stuffs
*/