#include "Client.h"

void Client::initialiseClient()
{
    //createClientWindow();
    runTcpClient();
}

void Client::runTcpClient()
{
    // Ask for the server address
    //sf::IpAddress server  = sf::IpAddress::getLocalAddress();
    //do
    //{
    //    std::cout << "Type the address or name of the server to connect to: ";
    //    std::cin >> server;
    //} while (server == sf::IpAddress::None);

    // Create a socket for communicating with the server
    //sf::TcpSocket socket;

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

	float timer = 0.0f;

    sf::RectangleShape rectServer;
    rectServer.setSize(sf::Vector2f(20, 20));
    rectServer.setFillColor(sf::Color::Red);
    rectServer.setPosition(sf::Vector2f(20, 20));

    sf::RectangleShape rectClient;
    rectClient.setSize(sf::Vector2f(20, 20));
    rectClient.setFillColor(sf::Color::Blue);
    rectClient.setPosition(sf::Vector2f(700, 20));

    windowClient.create(sf::VideoMode(800, 600, 32), "Client Window");
    windowClient.setFramerateLimit(60);

    //Clock for timing the 'dt' value
    sf::Clock clock;
    float sendRate = 0.5f;//update time
    float latency = 0.5f;//shadow time
    float gameSpeed = 1.0f;
    float gameTime = 0.0f;
    float startTime = sendRate * 3.0f;

    bool sleep = true;

    sf::Vector2f prevPosition, latestPosition, p2Position, p1Position;

    socket.setBlocking(false);//want to receive data each frame

    bool update = false;

    while (windowClient.isOpen())
    {
        //Get the time since the last frame in milliseconds
        float dt = clock.restart().asSeconds() * gameSpeed;
		timer += dt;

        sf::Event Event;
        while (windowClient.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
            {
                windowClient.close();
            }
            else if (Event.type == sf::Event::GainedFocus)
            {
                update = true;
            }
            else if (Event.type == sf::Event::LostFocus)
            {
                update = false;
            }


        }
        if (update)
        {
            gameTime += dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                //Move the Player to the right
                rectClient.move(rectSpeed, 0.0f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                //Move the Player to the left
                rectClient.move(-rectSpeed, 0.0f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                //Move the Player up
                rectClient.move(0.0f, -rectSpeed);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                //Move the Player down
                rectClient.move(0.0f, rectSpeed);
            }
            //latestPosition = sf::Vector3f(rect1.getPosition().x, rect1.getPosition().y, gameTime);
        }

       sf::Packet packet;
       socket.receive(packet);
       if (packet >> p2Position.x >> p2Position.y)
       {
           rectServer.setPosition(p2Position.x, p2Position.y);
       }

	   if (timer >= 0.2f)
	   {
		   if (prevPosition.x != rectClient.getPosition().x || prevPosition.y != rectClient.getPosition().y)
		   {
			   sf::Packet packetq;
			   packetq << rectClient.getPosition().x << rectClient.getPosition().y << gameTime;
			   socket.send(packetq);
		   }
		   timer = 0.0f;
	   }
       


        windowClient.draw(rectServer);
        windowClient.draw(rectClient);

        windowClient.display();
        windowClient.clear();
    }
    system("pause");

}

void Client::createClientWindow()
{
   // window.create(sf::VideoMode(800, 600, 32), "Client Window");
    //windowActive = true;
}

void Client::sendSocket(int x, int y)
{
    sf::Packet packet;
    packet << x << y;
    socket.send(packet);
}

sf::Vector2f Client::receiveSocket()
{
    sf::Vector2f newPosition;
    sf::Packet packet;
    socket.receive(packet);

    if (packet >> newPosition.x >> newPosition.y)
    {
        return newPosition;
    }
}
