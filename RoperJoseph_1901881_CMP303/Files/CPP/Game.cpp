#include "Game.h"

//Global container for messages
NetworkMessages networkMessagesContainer;

Game::Game(sf::RenderWindow* window)
{
	this->window = window;

	serverPlayer = new Player(window, sf::Vector2f(50, 250), "media/BoxPusher.png", 1);
	clientPlayer = new Player(window, sf::Vector2f(500, 50), "media/BoxPusherRed.png", 2);

	serverPlayer->setID(1);
	clientPlayer->setID(2);

	serverPlayer->setServerBool(true);
	clientPlayer->setClientBool(true);
	
	boxTest = new BoxManager(window, sf::Vector2f(300, 300));

	scoreLine = new ScoreLine(window);

	char who;
	std::cout << "Do you want to be a server (s) or a client (c)? ";
	std::cin >> who;

	if (who == 's')
	{
		std::cout << "Server Run" << std::endl;
		serverBool = true;
		networkObject = new ServerPlayer(port);
	}
	else if (who == 'c')
	{
		std::cout << "Client Run" << std::endl;
		clientBool = true;
		networkObject = new ClientPlayer(port);
	}
}

Game::~Game()
{
}

void Game::update(float dt)
{
	extern NetworkMessages networkMessagesContainer;
	
	gameTime += dt;

	if (serverBool)
	{
		//Server player update///////////////////////////
		playerCollisionUpdate(serverPlayer, clientPlayer, boxTest);
		boxCollisionUpdate(serverPlayer, boxTest);
		serverPlayer->Update(dt);
		serverPlayer->Move(serverPlayer->getVelocity());
		serverPlayer->PlayerRotate(serverPlayer->getAngle());
		boxTest->Move(boxTest->getVelocity());

		//Client receive packet//
		networkObject->receivePacket();
		clientPlayer->setPosition(networkObject->runPrediction(dt));
		clientPlayer->PlayerRotate(networkMessagesContainer.getPlayerMessage().angle);
		clientPlayer->setNewBoxPositionAddOn(networkMessagesContainer.getPlayerMessage().newBoxPositionAddOn);
		serverPlayer->setClientPlayerBounds(networkMessagesContainer.getPlayerMessage().clientPlayerBounds);
		clientPlayer->setClientPlayerBounds(networkMessagesContainer.getPlayerMessage().clientPlayerBounds);
		boxCollisionUpdate(clientPlayer, boxTest);
		/////Box update////////////////////////////////
		boxTest->Update(dt);
		boxTest->Move(boxTest->getVelocity());
		///////////////////////////////////////////////
		//scoreLineUpdate();
		scoreLine->setBoxPosition(boxTest->getPosition());
		scoreLine->Update(dt);

		//Send message every 15 frames to client
		if (latency % 4 == 0)
		{
			networkObject->sendMessage(serverPlayer);
			networkObject->sendMessage(boxTest);
			networkObject->sendMessage(scoreLine);
			///////////////////////////
		}



	}
	if (clientBool)
	{
		//Receive packet//
		//Server Player Move//
		networkObject->receivePacket();
		serverPlayer->setPosition(networkObject->runPrediction(dt));
		serverPlayer->PlayerRotate(networkMessagesContainer.getPlayerMessage().angle);

		networkObject->receivePacket();
		boxTest->setBoxPosition(networkMessagesContainer.getBoxMessage().position);
		
		networkObject->receivePacket();
		scoreLine->setScoreLineText(networkMessagesContainer.getScoreMessage().scoreRight, networkMessagesContainer.getScoreMessage().scoreLeft);
		//////////////////////////////////////////////////////
		
		//Client player update///////////////////////////
		playerCollisionUpdate(clientPlayer, serverPlayer, boxTest);
		boxCollisionUpdate(clientPlayer, boxTest);
		clientPlayer->Update(dt);
		clientPlayer->Move(clientPlayer->getVelocity());
		clientPlayer->PlayerRotate(clientPlayer->getAngle());
		clientPlayer->setTimeSent(gameTime);

		//Send message every 15 frames to server
		if (latency % 4 == 0)
		{
			networkObject->sendMessage(clientPlayer);
		}
	}

	latency++;
}


void Game::render(float dt)
{
	beginDraw();
	scoreLine->Render();
	boxTest->Render();
	serverPlayer->Render();
	clientPlayer->Render();
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


void Game::playerCollisionUpdate(Player* currentPlayer, Player* externalPlayer, BoxManager* box)
{
	//Collision
	FloatRect nextPos;//get players next position
	FloatRect currentPlayerBounds = currentPlayer->getSprite().getGlobalBounds();
	FloatRect externalPlayerBounds = externalPlayer->getSprite().getGlobalBounds();
	FloatRect boxBounds = box->getSprite().getGlobalBounds();
	currentPlayer->UpdateCollision(currentPlayerBounds, externalPlayerBounds, boxBounds);
}

void Game::boxCollisionUpdate(Player* player, BoxManager* box)
{
	Vector2f newBoxPositionAddOn = player->getNewBoxPositionAddOn();
	box->setVelocity(newBoxPositionAddOn);
	player->setNewBoxPositionAddOn(sf::Vector2f(0.0f, 0.0f));
}