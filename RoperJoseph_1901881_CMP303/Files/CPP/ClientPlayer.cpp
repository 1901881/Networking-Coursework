#include "ClientPlayer.h"

ClientPlayer::ClientPlayer(unsigned short port)
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
        serverPlayerMessageVector.push_back(p);
    }
}

ClientPlayer::~ClientPlayer()
{

}

void ClientPlayer::runNetwork(unsigned short port)
{
    // Ask for the server address
    socket.setBlocking(false);

    do
    {
        std::cout << "Type the ip address of the server to connect to: ";
        std::cin >> server;
    } while (server == sf::IpAddress::None);


    // Connect to the server
    if (socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

}


void ClientPlayer::sendMessage(ObjectInterface* object)
{
    sf::Packet packet = object->createPacket();
    socket.send(packet);
}

void ClientPlayer::receivePacket()
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
            break;
        }

    }
}

void ClientPlayer::receivePlayerPacket(sf::Packet packet)
{
    extern NetworkMessages networkMessagesContainer;
    PlayerMessage playerMessage;
    if (packet >> playerMessage.id >> playerMessage.velocityX >> playerMessage.velocityY >> playerMessage.angle >> playerMessage.timeSent >> playerMessage.position.x >> playerMessage.position.y >> playerMessage.newBoxPositionAddOn.x >> playerMessage.newBoxPositionAddOn.y)
    {
        sf::Vector2f playerPosition = playerMessage.position;
        networkMessagesContainer.setPlayerMessage(playerMessage);
        serverPlayerMessageVector.push_back(playerMessage);
    }
}

void ClientPlayer::receiveBoxPacket(sf::Packet packet)
{
    extern NetworkMessages networkMessagesContainer;
    BoxMessage boxMessage;

    if (packet >> boxMessage.id >> boxMessage.velocityX >> boxMessage.velocityY >> boxMessage.position.x >> boxMessage.position.y)
    {
        networkMessagesContainer.setBoxMessage(boxMessage);
    }
}

void ClientPlayer::receiveScorePacket(sf::Packet packet)
{
    extern NetworkMessages networkMessagesContainer;
    ScoreMessage scoreMessage;

    if (packet >> scoreMessage.scoreLeft >> scoreMessage.scoreRight)
    {
        networkMessagesContainer.setScoreMessage(scoreMessage);
    }
}

sf::Vector2f ClientPlayer::runPrediction(float dt)
{
    extern NetworkMessages networkMessagesContainer;
    const int msize = serverPlayerMessageVector.size();

    //waits until the vector is filled with the server sides data before running prediction
    if (serverPlayerMessageVector[2].position.x == -2000)
    {
        return sf::Vector2f(networkMessagesContainer.getPlayerMessage().position);
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

    float speed = ((msg0.position.x - msg1.position.x) - (msg0.position.y - msg1.position.y)) / (msg0.timeSent - msg1.timeSent);
    float displacement = speed * (dt - msg0.timeSent);
    float nextPositionX = msg0.position.x + displacement;
    float nextPositionY = msg0.position.y + displacement;
    return sf::Vector2f(nextPositionX, nextPositionY);
}

void ClientPlayer::addServerPlayerMessage(PlayerMessage& msg)
{
    //when a new message is sent it shuffles all the other messages into the next slot in memory
    serverPlayerMessageVector[2] = serverPlayerMessageVector[1];
    serverPlayerMessageVector[1] = serverPlayerMessageVector[0];
    serverPlayerMessageVector[0] = msg;
}

