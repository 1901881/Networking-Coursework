#include "ClientPlayer.h"

ClientPlayer::ClientPlayer(unsigned short port)
{
    runTcpClient(port);

    //maybe change this to nand
    for (int x = 0; x < 3; x++)
    {
        PlayerMessage p;
        p.velocityX = -2000;//arbitrary values used for testing 
        p.velocityY = -2000;
        p.angle = -2000;
        p.id = -2000;
        serverPlayerMessageVector.push_back(p);
    }
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

void ClientPlayer::receiveScoreMessage()
{
    ScoreMessage scoreMessage;
    Packet packet;
    socket.receive(packet);
    if (packet >> scoreMessage.scoreLeft >> scoreMessage.scoreRight)
    {
        this->scoreMessage = scoreMessage;
    }
}

sf::Vector2f ClientPlayer::runPrediction(float dt)
{
    const int msize = serverPlayerMessageVector.size();

    //waits until the vector is filled with the client sides data before running prediction
    if (serverPlayerMessageVector[2].velocityX == -2000)
    {
        return sf::Vector2f(serverPlayerMessage.velocityX, serverPlayerMessage.velocityY);
    }
    int msg0Size = msize - 1;
    int msg1Size = msize - 2;
    int msg2Size = msize - 3;
    const PlayerMessage& msg0 = serverPlayerMessageVector[msg0Size];
    const PlayerMessage& msg1 = serverPlayerMessageVector[msg1Size];
    const PlayerMessage& msg2 = serverPlayerMessageVector[msg2Size];

    //Linear
    //Next position = previous position + displacement
    //displacement = speed*time
    //speed = distance between last two position / time between last two positions

    float speed = ((msg0.velocityX - msg1.velocityX) - (msg0.velocityY - msg1.velocityY)) / (msg0.timeSent - msg1.timeSent);
    float displacement = speed * (dt - msg0.timeSent);
    float nextPositionX = msg0.velocityX + displacement;
    float nextPositionY = msg0.velocityY + displacement;
    return sf::Vector2f(nextPositionX, nextPositionY);

    //add latency

    /*
    need to get liner prediction calculation

    need delta time and time sent

    save velocity when sent

    ignore null references

    set as predictid velocity
    then use that in game to move player.
    */

}

void ClientPlayer::addServerPlayerMessage(PlayerMessage& msg)
{
    //when a new message is sent it shuffles all the other messages into the next slot in memory
    serverPlayerMessageVector[2] = serverPlayerMessageVector[1];
    serverPlayerMessageVector[1] = serverPlayerMessageVector[0];
    serverPlayerMessageVector[0] = msg;
}

/*
receive message

then get infoe and place it in stuffs

make it so a ceratin amount of messages are sent per second
*/