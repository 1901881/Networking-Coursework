#include "Server.h"

void Server::initialiseServer()
{
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


    /*
    make a window
    make a player - rectangle
    set the player position


    i want the while window is open to be in the game class

    create window should be here can just have a bool function 
    returning if its live or not in the game class


    */



    //// Send a message to the connected client
    //const char out[] = "Hi, I'm the server";
    //if (socket.send(out, sizeof(out)) != sf::Socket::Done)
    //    return;
    //std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

    //// Receive a message back from the client
    //char in[128];
    //std::size_t received;
    //if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
    //    return;
    //std::cout << "Answer received from the client: \"" << in << "\"" << std::endl;
   // system("pause");


    rectServer.setSize(sf::Vector2f(20, 20));
    rectServer.setFillColor(sf::Color::Red);
    rectServer.setPosition(sf::Vector2f(20, 20));

    rectClient.setSize(sf::Vector2f(20, 20));
    rectClient.setFillColor(sf::Color::Blue);
    rectClient.setPosition(sf::Vector2f(700, 20));

    rectClientGhost.setSize(sf::Vector2f(20, 20));
    rectClientGhost.setFillColor(sf::Color::Green);//0.0f, 0.0f, 1.0f, 128
    rectClientGhost.setPosition(sf::Vector2f(700, 20));

	for (int x = 0; x < 3; x++)
	{
		PlayerMessage p;
		p.x = -2000;
		p.y = -2000;
		p.timeSent = -2000;
		playerMessages.push_back(p);
	}

    window.create(sf::VideoMode(800, 600, 32), "Server Window");
    window.setFramerateLimit(60);

    //Clock for timing the 'dt' value
    sf::Clock clock;
    float sendRate = 0.5f;//update time
    float latency = 0.5f;//shadow time
    float gameSpeed = 1.0f;
    float gameTime = 0.0f;
    float startTime = sendRate * 3.0f;

    sf::Vector2f prevPosition, latestPosition, p2Position, p1Position;

    socket.setBlocking(false);//want to receive data each frame

    bool update = false;

    bool sleep = true;

    while (window.isOpen())
    {
        
        //Get the time since the last frame in milliseconds
        float dt = clock.restart().asSeconds() * gameSpeed;

        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
            {
                window.close();
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


        prevPosition = sf::Vector2f(rectServer.getPosition().x, rectServer.getPosition().y);

        if (update)
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
            //latestPosition = sf::Vector3f(rect1.getPosition().x, rect1.getPosition().y, gameTime);
        }

        
  
        //Checks if the player has moved if yes the new position data is sent
        if (prevPosition.x != rectServer.getPosition().x || prevPosition.y != rectServer.getPosition().y)
        {
            sf::Packet packet;
            packet << rectServer.getPosition().x << rectServer.getPosition().y;
            socket.send(packet);

           
        }

        float sentTime = 2.1f;
        sf::Packet packet;
        socket.receive(packet);
        if (packet >> p2Position.x >> p2Position.y >> sentTime)
        {
            //rectClient.setPosition(p2Position.x, p2Position.y);
           
			PlayerMessage msg;
			msg.x = p2Position.x;
			msg.y = p2Position.y;
			msg.timeSent = gameTime;
			addMessage(msg);
            
        }


        rectClientGhost.setPosition(runPrediction(gameTime));
        rectClient.setPosition(runPrediction(gameTime));

        window.draw(rectServer);
        window.draw(rectClient);
        window.draw(rectClientGhost);

        window.display();
        window.clear();
    }
    system("pause");
}

void Server::createServerWindow()
{
   window.create(sf::VideoMode(800, 600, 32), "Server Window");
   windowActive = true;
}

void Server::sendSocket(int prevX, int prevY, int rectX, int rectY, sf::Packet packet)
{
    //sf::Packet packet;
    //Checks if the player has moved if yes the new position data is sent
   // if (prevX != rectX || prevY != rectY)
   // {
    packet << rectX << rectY;
    socket.send(packet);
   // }
}

void Server::receiveSocket()
{
    int x, y;
    sf::Packet packet;
    socket.receive(packet);
    if (packet >> x >> y)
    {
        rectClient.setPosition(x, y);
    }
}

void Server::addMessage(PlayerMessage& msg)
{
 //   if (playerMessages.size() >= 3)
 //   {
	//	playerMessages.pop_back();
 //   }
	//playerMessages.push_back(msg);

	
	playerMessages[2] = playerMessages[1];
	playerMessages[1] = playerMessages[0];
	playerMessages[0] = msg;
}

void Server::push_front(PlayerMessage& msg)
{
	/*
	memmove
	source, destination, size
	*/
	
}

sf::Vector2f Server::runPrediction(float gameTime)
{

	
	sf::Vector2f clientPosition;
	clientPosition = rectClient.getPosition();

    const int msize = playerMessages.size();
    if (playerMessages[2].x == -2000) 
	{
		//return clientPosition;
		return sf::Vector2f(100, 100);
    }
    int msg0Size = msize - 1;
    int msg1Size = msize - 2;
    int msg2Size = msize - 3;
    const PlayerMessage& msg0 = playerMessages[msg0Size];
    const PlayerMessage& msg1 = playerMessages[msg1Size];
    const PlayerMessage& msg2 = playerMessages[msg2Size];

    // FIXME: Implement prediction here!
    // You have:
    // - the history of position messages received, in "m_Messages"
    //   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
    // - the current time, in "gameTime"
    //
    // You need to update:
    // - the predicted position at the current time, in "predictedX" and "predictedY"

   // predictedX = msg0.x;
    //predictedY = msg0.y;

    //predictedX = 40.0f;
    //predictedY = 20.0f;
    //return sf::Vector2f(predictedX, predictedY);

    //Linear
    //Next position = previous position + displacement
    //displacement = speed*time
    //speed = distance between last two position / time between last two positions

    float speed = ((msg0.x - msg1.x) - (msg0.y - msg1.y)) / (msg0.timeSent - msg1.timeSent);
    float displacement = speed * (gameTime - msg0.timeSent);
    float nextPositionX = msg0.x + displacement;
    float nextPositionY = msg0.y + displacement;
    return sf::Vector2f(nextPositionX, nextPositionY);

    //Quadratic
    //S = ut +1/2at²
    //next position = previous position + displacement
    //displacement = speed(at last msg) * time (since last msg) + 0.5 * acceleration * time²
    //speed = distance beteween  last two position/ time between last two positions
    //acceleration = difference in speed at the last two positioms / time between those positions

    //float speed1 = ((msg0.x - msg1.x) - (msg0.y - msg1.y)) / (msg0.timeSent - msg1.timeSent);
    //float speed2 = ((msg1.x - msg2.x) - (msg1.y - msg2.y)) / (msg1.timeSent - msg2.timeSent);
    //float acceleration = (speed1 - speed2) / (msg0.timeSent - msg2.timeSent);
    //float displacement = speed1 * (gameTime - msg0.timeSent) + (0.5 * acceleration * powf(gameTime - msg0.timeSent, 2));
    //float nextPositionX = msg0.x + displacement;
    //float nextPositionY = msg0.y + displacement;
    //return sf::Vector2f(nextPositionX, nextPositionY);
}
