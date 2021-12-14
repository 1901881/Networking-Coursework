#include "Client.h"

void Client::initialiseClient()
{
	rectServer.setSize(sf::Vector2f(20, 20));
	rectServer.setFillColor(sf::Color::Red);
	rectServer.setPosition(sf::Vector2f(20, 20));

	rectClient.setSize(sf::Vector2f(20, 20));
	rectClient.setFillColor(sf::Color::Blue);
	rectClient.setPosition(sf::Vector2f(700, 20));

    runTcpClient();
}

void Client::runTcpClient()
{
    // Connect to the server
    if (socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

    windowClient.create(sf::VideoMode(800, 600, 32), "Client Window");
    windowClient.setFramerateLimit(60);

    socket.setBlocking(false);//want to receive data each frame

    while (windowClient.isOpen())
    {
        //Get the time since the last frame in milliseconds
        float dt = clock.restart().asSeconds() * gameSpeed;
		timer += dt;

		event();

		updateClient(dt);

		//Receives the packet from the server 
		//used for updating the servers object
       sf::Packet packet;
       socket.receive(packet);
       if (packet >> p2Position.x >> p2Position.y)
       {
           rectServer.setPosition(p2Position.x, p2Position.y);
       }

	   //timer is used to limit the amount of packets being sent
	   if (timer >= 0.2f)
	   {
		   if (prevPosition.x != rectClient.getPosition().x || prevPosition.y != rectClient.getPosition().y)
		   {
			   sf::Packet packetq;
			   packetq << rectClient.getPosition().x << rectClient.getPosition().y << gameTime;
			   socket.send(packetq);
		   }
		   timer = 0.0f;//timer is reset for the next packet
	   }

	   windowDraw();
    }
    system("pause");

}

void Client::windowDraw()
{
	//Renders the relevant data onto the screen
	windowClient.draw(rectServer);
	windowClient.draw(rectClient);

	windowClient.display();
	windowClient.clear();
}

void Client::updateClient(float dt)
{
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
	}
}

void Client::event()
{
	//Keeps the sfml window active when run
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
}