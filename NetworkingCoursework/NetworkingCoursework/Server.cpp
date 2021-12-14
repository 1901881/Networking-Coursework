#include "Server.h"

void Server::initialiseServer()
{
	//Setting up the moveable object in the program
	rectServer.setSize(sf::Vector2f(20, 20));
	rectServer.setFillColor(sf::Color::Red);
	rectServer.setPosition(sf::Vector2f(20, 20));

	rectClient.setSize(sf::Vector2f(20, 20));
	rectClient.setFillColor(sf::Color::Blue);
	rectClient.setPosition(sf::Vector2f(700, 20));

	//the green object represents the prediction for the clients object
	rectClientGhost.setSize(sf::Vector2f(20, 20));
	rectClientGhost.setFillColor(sf::Color::Green);
	rectClientGhost.setPosition(sf::Vector2f(700, 20));

	//initialises the player messages for prediction to run by filling it up by 3 slots 
	for (int x = 0; x < 3; x++)
	{
		PlayerMessage p;
		p.x = -2000;//arbitrary values used for testing 
		p.y = -2000;
		p.timeSent = -2000;
		playerMessages.push_back(p);
	}

    //createServerWindow();
    runTcpServer();
}

void Server::runTcpServer()
{
	// Listen to the given port for incoming connections
	if (listener.listen(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

	// Wait for a connection
	if (listener.accept(socket) != sf::Socket::Done)
		return;
	std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;


	window.create(sf::VideoMode(800, 600, 32), "Server Window");
	window.setFramerateLimit(60);

	socket.setBlocking(false);//so it receives data each frame

	while (window.isOpen())
	{
		//Get the time since the last frame in milliseconds
		float dt = clock.restart().asSeconds() * gameSpeed;

		event();

		//used when sending data to the client
		prevPosition = sf::Vector2f(rectServer.getPosition().x, rectServer.getPosition().y);

		update(dt);

		//Checks if the player has moved if yes the new position data is sent to the client
		//for use to update the server object position on the clients side
		if (prevPosition.x != rectServer.getPosition().x || prevPosition.y != rectServer.getPosition().y)
		{
			sf::Packet packet;
			packet << rectServer.getPosition().x << rectServer.getPosition().y;
			socket.send(packet);
		}

		//receives new position data from the client
		sf::Packet packet;
		socket.receive(packet);
		//if the packet received is filled with the correct data the client objects position is sent
		if (packet >> p2Position.x >> p2Position.y >> sentTime)
		{
			rectClient.setPosition(p2Position.x, p2Position.y);
			//sets us a message filled with the client objects position and time the data was sent
			//this is all used for the prediction
			PlayerMessage msg;
			msg.x = p2Position.x;
			msg.y = p2Position.y;
			msg.timeSent = gameTime;
			addMessage(msg);
		}

		rectClientGhost.setPosition(runPrediction(gameTime));

		windowDraw();
	}
	system("pause");
}

void Server::addMessage(PlayerMessage& msg)
{
	//when a new message is sent it shuffles all the other messages into the next slot in memory
	playerMessages[2] = playerMessages[1];
	playerMessages[1] = playerMessages[0];
	playerMessages[0] = msg;
}

sf::Vector2f Server::runPrediction(float gameTime)
{
	sf::Vector2f clientPosition;
	clientPosition = rectClient.getPosition();

    const int msize = playerMessages.size();

	//waits until the vector is filled with the client sides data before running prediction
    if (playerMessages[2].x == -2000) 
	{
		return clientPosition;
    }
    int msg0Size = msize - 1;
    int msg1Size = msize - 2;
    int msg2Size = msize - 3;
    const PlayerMessage& msg0 = playerMessages[msg0Size];
    const PlayerMessage& msg1 = playerMessages[msg1Size];
    const PlayerMessage& msg2 = playerMessages[msg2Size];

    //Linear
    //Next position = previous position + displacement
    //displacement = speed*time
    //speed = distance between last two position / time between last two positions

    //float speed = ((msg0.x - msg1.x) - (msg0.y - msg1.y)) / (msg0.timeSent - msg1.timeSent);
    //float displacement = speed * (gameTime - msg0.timeSent);
    //float nextPositionX = msg0.x + displacement;
    //float nextPositionY = msg0.y + displacement;
    //return sf::Vector2f(nextPositionX, nextPositionY);

    //Quadratic
    //S = ut +1/2at²
    //next position = previous position + displacement
    //displacement = speed(at last msg) * time (since last msg) + 0.5 * acceleration * time²
    //speed = distance beteween  last two position/ time between last two positions
    //acceleration = difference in speed at the last two positioms / time between those positions

    float speed1 = ((msg0.x - msg1.x) - (msg0.y - msg1.y)) / (msg0.timeSent - msg1.timeSent);
    float speed2 = ((msg1.x - msg2.x) - (msg1.y - msg2.y)) / (msg1.timeSent - msg2.timeSent);
    float acceleration = (speed1 - speed2) / (msg0.timeSent - msg2.timeSent);
    float displacement = speed1 * (gameTime - msg0.timeSent) + (0.5 * acceleration * powf(gameTime - msg0.timeSent, 2));
    float nextPositionX = msg0.x + displacement;
    float nextPositionY = msg0.y + displacement;
    return sf::Vector2f(nextPositionX, nextPositionY);
}

void Server::update(float dt)
{
	//handles the input for the servers object and updates gametime used for prediction based off of delta time
	if (updateBool)
	{
		gameTime += dt;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//Move the Player to the right
			rectServer.move(rectSpeed, 0.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//Move the Player to the left
			rectServer.move(-rectSpeed, 0.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//Move the Player up
			rectServer.move(0.0f, -rectSpeed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//Move the Player down
			rectServer.move(0.0f, rectSpeed);
		}
	}
}

void Server::event()
{
	//Keeps the sfml window active when run
	while (window.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
		else if (Event.type == sf::Event::GainedFocus)
		{
			updateBool = true;
		}
		else if (Event.type == sf::Event::LostFocus)
		{
			updateBool = false;
		}
	}
}

void Server::windowDraw()
{
	//Renders the relevant data to the screen
	window.draw(rectServer);
	window.draw(rectClient);
	window.draw(rectClientGhost);

	window.display();
	window.clear();
}
