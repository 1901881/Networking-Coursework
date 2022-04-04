#include "Game.h"

//Global container for messages
NetworkMessages networkMessagesContainer;

Game::Game(sf::RenderWindow* window)
{
	// Set window and input for the Gameulation
	this->window = window;



	serverPlayer = new Player(window, sf::Vector2f(50, 250), "media/BoxPusher.png", 1);

	//for (int i = 0; i < boxAmount; i++) {
	//	sf::Vector2f boxPosition = sf::Vector2f(i * 70, i * 70);
	//	//boxManager[i] = new BoxManager(window, boxPosition);
	//	BoxManager* box = new BoxManager(window, boxPosition);
	//	boxes.push_back(box);
	//}
	
	boxTest = new BoxManager(window, sf::Vector2f(300, 300));

	scoreLine = new ScoreLine(window);

	//initScoreLine();
	//initText();

	// Client or server ?
	char who;
	std::cout << "Do you want to be a server (s) or a client (c)? ";
	std::cin >> who;

	// Test the TCP protocol
	if (who == 's')
	{
		std::cout << "Server Run" << std::endl;
		//server = new ServerPlayer(port);
		serverBool = true;
		//serverPlayer = new ServerPlayer(window);
		//serverPlayer->runTcpServer(port);
		networkObject = new ServerPlayer(port);
	}
	else if (who == 'c')
	{
		std::cout << "Client Run" << std::endl;
		//client = new ClientPlayer(port);
		clientBool = true;
		//clientPlayer = new ClientPlayer();
		//clientPlayer->runTcpClient(port);
		networkObject = new ClientPlayer(port);
	}
}

Game::~Game()
{
/*
get three time stamps from server
use them to figure out difference and use that variable to sync times
*/
}

void Game::update(float dt)
{
	extern NetworkMessages networkMessagesContainer;
	

	gameTime += dt;

	if (serverBool)
	{
		playerCollisionUpdate();
		boxCollisionUpdate();

		//Server player update///////////////////////////
		serverPlayer->Update(dt);
		sf::Vector2f serverPlayerVelocity = serverPlayer->getVelocity();
		int serverPlayerAngle = serverPlayer->getAngle();
		serverPlayer->Move(serverPlayerVelocity);
		serverPlayer->PlayerRotate(serverPlayerAngle);

		//if(rand variable = 2 play)

		//std::cout << "Game cpp: " << serverPlayer->getSprite().getRotation() << std::endl;
		///////////////////////////////////////////////

		/////Box update////////////////////////////////
		boxTest->Update(dt);
		sf::Vector2f boxVelocity = boxTest->getVelocity();
		boxTest->Move(boxVelocity);
		///////////////////////////////////////////////


		//scoreLineUpdate();
		scoreLine->setBoxPosition(boxTest->getPosition());
		scoreLine->Update(dt);

		if (latency % 4 == 0)
		{
			//PlayerMessage serverPlayerMessage;
			//serverPlayerMessage.id = 1;
			//serverPlayerMessage.velocityX = serverPlayerVelocity.x;
			//serverPlayerMessage.velocityY = serverPlayerVelocity.y;
			//serverPlayerMessage.angle = serverPlayerAngle;
			//serverPlayerMessage.timeSent = gameTime;
			//serverPlayerMessage.position = serverPlayer->getPosition();
			//server->createPlayerMessage(serverPlayerMessage);

			//BoxMessage boxMessage;
			//boxMessage.id = 3;
			//boxMessage.position = boxTest->getBoxPosition();
			//boxMessage.velocityX = boxVelocity.x;
			//boxMessage.velocityY = boxVelocity.y;
			//server->createBoxMessage(boxMessage);


			//server->createScoreMessage(scoreLeft, scoreRight);

			//networkObject->sendMessage();
			
			

			serverPlayer->setTimeSent(gameTime);
			networkObject->sendMessage(serverPlayer);

			networkObject->sendMessage(boxTest);

			networkObject->sendMessage(scoreLine);
			
		}

	}
	if (clientBool)
	{

		//client->receivePlayerMessage();
		//serverPlayer->PlayerRotate(client->getServerPlayerMessage().angle);

		//serverPlayer->setPosition(client->runPrediction(dt));
		////std::cout << "Game cpp client side: " << client->getServerPlayerMessage().angle << std::endl;

		////update box here 
		//client->receiveBoxMessage();
		//boxTest->setBoxPosition(client->getBoxMessage().position);

		////Update score
		//client->receiveScoreMessage();
		//scoreLeft = client->getScoreMessage().scoreLeft;
		//scoreRight = client->getScoreMessage().scoreRight;
		//setScoreLineText();
		

		//Server Player Move//
		networkObject->receivePacket();
		//serverPlayer->setPosition(networkMessagesContainer.getPlayerMessage().position);
		serverPlayer->setPosition(networkObject->runPrediction(dt));
		serverPlayer->PlayerRotate(networkMessagesContainer.getPlayerMessage().angle);

		networkObject->receivePacket();
		boxTest->setBoxPosition(networkMessagesContainer.getBoxMessage().position);
		
		networkObject->receivePacket();
		scoreLine->setScoreLineText(networkMessagesContainer.getScoreMessage().scoreRight, networkMessagesContainer.getScoreMessage().scoreLeft);

		//networkObject->receivePacket();
		//scoreLine->setScoreLineText();
		//boxTest->setBoxPosition(networkMessagesContainer.getBoxMessage().position);
		//networkObject->receivePacket();
		//scoreLeft = networkMessagesContainer.getScoreMessage().scoreLeft;
		//scoreRight = networkMessagesContainer.getScoreMessage().scoreRight;
		//setScoreLineText();

	}




	latency++;
}


void Game::render(float dt)
{
	beginDraw();
	//window->draw(scoreLine);
	


	//for (int i = 0; i < boxAmount; i++) {
	//	//boxManager[i]->Render();
	//}

	//for (auto& box : boxes)
	//{
	//	box->Render();
	//}

	scoreLine->Render();
	boxTest->Render();
	serverPlayer->Render();


	//window->draw(titleText);
	//window->draw(scoreTextLeft);
	//window->draw(scoreTextRight);
	endDraw();
}


void Game::beginDraw()
{
	// Set window colour to black when clearing
	window->clear(sf::Color(18, 33, 43)); //Color Background
}

void Game::endDraw()
{
	window->display();
}

void Game::initScoreLine()
{
	////init road line
	//scoreLine.setSize(sf::Vector2f(5.0f, window->getSize().y));
	//scoreLine.setOrigin(sf::Vector2f((window->getSize().x) / 2.0f, 0.0f));
	//scoreLine.setPosition(sf::Vector2f(window->getSize().x, 0.0f));
}

void Game::initText()
{
	//if (!font.loadFromFile("media/RetroGaming.ttf"))
	//{
	//	//handle error
	//}
	//titleText.setFont(font);
	//titleText.setString("Box Pusher");
	//titleText.setFillColor(sf::Color::White);
	//titleText.setCharacterSize(25);


	//std::string scoreStringLeft = std::to_string(scoreLeft);
	//scoreTextLeft.setFont(font);
	//scoreTextLeft.setString(scoreStringLeft);
	//scoreTextLeft.setFillColor(sf::Color::White);
	//scoreTextLeft.setCharacterSize(35);
	//scoreTextLeft.setPosition(window->getSize().y / 2 + 30, 0);

	//std::string scoreStringRight = std::to_string(scoreRight);
	//scoreTextRight.setFont(font);
	//scoreTextRight.setString(scoreStringRight);
	//scoreTextRight.setFillColor(sf::Color::White);
	//scoreTextRight.setCharacterSize(35);
	//scoreTextRight.setPosition(window->getSize().y / 2 + 120, 0);
}

void Game::scoreLineUpdate()
{
	/*if (boxTest->getSprite().getPosition().x > scoreLine.getOrigin().x)
	{
		scoreLeft = 0;
		scoreRight = 1;
	}
	else
	{
		scoreLeft = 1;
		scoreRight = 0;
	}
 
	setScoreLineText();*/
}

void Game::setScoreLineText()
{
	/*std::string scoreStringRight = std::to_string(scoreRight);
	scoreTextRight.setString(scoreStringRight);

	std::string scoreStringLeft = std::to_string(scoreLeft);
	scoreTextLeft.setString(scoreStringLeft);*/
}

void Game::playerCollisionUpdate()
{
	//Collision
	FloatRect nextPos;//get players next position
	//for (auto &box : boxes)
	FloatRect playerBounds = serverPlayer->getSprite().getGlobalBounds();
	//FloatRect playerBounds = serverPlayer->getPlayer()->getSprite().getGlobalBounds();
	FloatRect boxBounds = boxTest->getSprite().getGlobalBounds();
	nextPos = playerBounds;
	nextPos.left += serverPlayer->getVelocity().x;
	//nextPos.left += serverPlayer->getPlayer()->getVelocity().x;
	nextPos.top += serverPlayer->getVelocity().y;
	//nextPos.top += serverPlayer->getPlayer()->getVelocity().y;
	serverPlayer->UpdateCollision(playerBounds, boxBounds);
	//serverPlayer->getPlayer()->UpdateCollision(playerBounds, boxBounds);
}

void Game::boxCollisionUpdate()
{
	Vector2f newBoxPositionAddOn = serverPlayer->getNewBoxPositionAddOn();
	//Vector2f newBoxPositionAddOn = serverPlayer->getPlayer()->getNewBoxPositionAddOn();
	boxTest->setVelocity(newBoxPositionAddOn);
	//boxTest->Update(dt);

	serverPlayer->setNewBoxPositionAddOn(sf::Vector2f(0.0f, 0.0f));
	//serverPlayer->getPlayer()->setNewBoxPositionAddOn(sf::Vector2f(0.0f, 0.0f));

	sf::Vector2f boxPosition = boxTest->getSprite().getPosition();
	//sf::Vector2f screenSize = sf::Vector2f(window->getSize().y / 2.0f);
}

/*
Struct message

message type enum

const char array

message size

max size message = 400

memcpy mempaste

one general send function

one general receive function


player has create packet function

create pointer to struct BaseMessage

entity pointer 



*/