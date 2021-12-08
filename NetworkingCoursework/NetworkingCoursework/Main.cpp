#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<string>
#include<iostream>

using namespace std;
using namespace sf;

sf::Vector2f Prediction(float gameTime, Vector3f prevPosition, Vector3f latestPosition)
{
	/*
	Need most recent position, 2nd most recent and 3rd most recent
	*/

	Vector2f predictedPos(-1.0f, -1.0f);


	float speed = ((latestPosition.x - prevPosition.x) - (latestPosition.y - prevPosition.y)) / (latestPosition.z - prevPosition.z);
	float displacement = speed * (gameTime - latestPosition.z);
	float nextPositionX = latestPosition.x + displacement;
	float nextPositionY = latestPosition.y + displacement;
	predictedPos = sf::Vector2f(nextPositionX, nextPositionY);
	return predictedPos;

	//mkae the time saving different
	//like the tank code
	//then use quadratic prediction

	//add latency

}

int main()
{
	IpAddress ip = IpAddress::getLocalAddress();
	TcpSocket socket;
	char connectionType;

	std::cout << "(s) for server, (c) for client: ";
	std::cin >> connectionType;

	if (connectionType == 's')
	{
		TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else
	{
		socket.connect(ip, 2000);
	}

	RectangleShape rect1, rect2, rectGhost;

	rect1.setSize(Vector2f(20, 20));
	rect2.setSize(Vector2f(20, 20));
	rectGhost.setSize(Vector2f(20, 20));

	rect1.setFillColor(Color::Red);
	rect2.setFillColor(Color::Blue);
	rectGhost.setFillColor(Color::Green);

	RenderWindow window(VideoMode(800, 600, 32), "Packets");
	window.setFramerateLimit(60);
	Vector3f prevPosition, latestPosition, p2Position, p1Position;
	Vector2f ghostPos;

	socket.setBlocking(false);//want to receive data each frame

	bool update = false;

	//Clock for timing the 'dt' value
	sf::Clock clock;
	float sendRate = 0.01f;//update time
	float latency = 0.1f;//shadow time
	float gameSpeed = 1.0f;
	float gameTime = 0.0f;
	float startTime = sendRate * 3.0f;

	while (window.isOpen())
	{
		//Get the time since the last frame in milliseconds
		float dt = clock.restart().asSeconds() * gameSpeed;

		Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == Event::Closed || Event.key.code == Keyboard::Escape)
			{
				window.close();
			}
			else if (Event.type == Event::GainedFocus)
			{
				update = true;
			}
			else if (Event.type == Event::LostFocus)
			{
				update = false;
			}


		}

		prevPosition = sf::Vector3f(rect1.getPosition().x, rect1.getPosition().y, gameTime);

		if (update)
		{
			gameTime += dt;
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				//Move the Player to the right
				rect1.move(0.5f, 0.0f);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A))
			{
				//Move the Player to the left
				rect1.move(-0.5f, 0.0f);
			}
			else if (Keyboard::isKeyPressed(Keyboard::W))
			{
				//Move the Player up
				rect1.move(0.0f, -0.5f);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				//Move the Player down
				rect1.move(0.0f, 0.5f);
			}
			latestPosition = sf::Vector3f(rect1.getPosition().x, rect1.getPosition().y, gameTime);
		}
		

		ghostPos = Prediction(gameTime, prevPosition, latestPosition);
		rectGhost.setPosition(ghostPos.x, ghostPos.y);
		
		Packet packet;
		//Checks if the player has moved if yes the new position data is sent
		if (prevPosition.x != rect1.getPosition().x || prevPosition.y != rect1.getPosition().y)
		{
			packet << rect1.getPosition().x << rect1.getPosition().y;
			socket.send(packet);
		}
		socket.receive(packet);
		if (packet >> p2Position.x >> p2Position.y)
		{
			rect2.setPosition(p2Position.x, p2Position.y);
		}

		window.draw(rect1);
		window.draw(rect2);
		window.draw(rectGhost);

		window.display();
		window.clear();
	}

	

	system("pause");
}

/*
You should send new data only when there is a change in direction,
and calculate other player position locally.
Then everything works fine.

set frame limit to 60

put a cooldown

for multiple computers you need to use: getPublicAddress
*/