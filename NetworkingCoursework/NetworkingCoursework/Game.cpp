#include "Game.h"

//Global container for messages
NetworkMessages networkMessagesContainer;

Game::Game(sf::RenderWindow* window)
{
	// Set window and input for the Gameulation
	this->window = window;



	serverPlayer = new Player(window, sf::Vector2f(50, 250), "media/BoxPusher.png", 1);
	clientPlayer = new Player(window, sf::Vector2f(500, 50), "media/BoxPusherRed.png", 2);

	serverPlayer->setServerBool(true);
	clientPlayer->setClientBool(true);
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
		//Server player update///////////////////////////
		playerCollisionUpdate(serverPlayer, boxTest);
		boxCollisionUpdate(serverPlayer, boxTest);
		serverPlayer->Update(dt);
		//sf::Vector2f serverPlayerVelocity = serverPlayer->getVelocity();
		//int serverPlayerAngle = serverPlayer->getAngle();
		serverPlayer->Move(serverPlayer->getVelocity());
		serverPlayer->PlayerRotate(serverPlayer->getAngle());

		boxTest->Move(boxTest->getVelocity());

		//Client Player Move//
		networkObject->receivePacket();
		//clientPlayer->setPosition(networkMessagesContainer.getPlayerMessage().position);
		clientPlayer->setPosition(networkObject->runPrediction(dt));
		clientPlayer->PlayerRotate(networkMessagesContainer.getPlayerMessage().angle);
		clientPlayer->setNewBoxPositionAddOn(networkMessagesContainer.getPlayerMessage().newBoxPositionAddOn);
		playerCollisionUpdate(clientPlayer, boxTest);
		boxCollisionUpdate(clientPlayer, boxTest);
		//clientPlayer->Update(dt);
		// 
		/////Box update////////////////////////////////
		boxTest->Update(dt);
		//sf::Vector2f boxVelocity = boxTest->getVelocity();
		boxTest->Move(boxTest->getVelocity());
		///////////////////////////////////////////////
		//scoreLineUpdate();
		scoreLine->setBoxPosition(boxTest->getPosition());
		scoreLine->Update(dt);

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
		//Server Player Move//
		networkObject->receivePacket();
		//serverPlayer->setPosition(networkMessagesContainer.getPlayerMessage().position);
		serverPlayer->setPosition(networkObject->runPrediction(dt));
		serverPlayer->PlayerRotate(networkMessagesContainer.getPlayerMessage().angle);

		networkObject->receivePacket();
		boxTest->setBoxPosition(networkMessagesContainer.getBoxMessage().position);
		
		networkObject->receivePacket();
		scoreLine->setScoreLineText(networkMessagesContainer.getScoreMessage().scoreRight, networkMessagesContainer.getScoreMessage().scoreLeft);
		//////////////////////////////////////////////////////
		
		//Client player update///////////////////////////
		playerCollisionUpdate(clientPlayer, boxTest);
		boxCollisionUpdate(clientPlayer, boxTest);
		clientPlayer->Update(dt);
		sf::Vector2f clientPlayerVelocity = clientPlayer->getVelocity();
		int clientPlayerAngle = clientPlayer->getAngle();
		clientPlayer->Move(clientPlayerVelocity);
		clientPlayer->PlayerRotate(clientPlayerAngle);
		clientPlayer->setTimeSent(gameTime);
		

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
	clientPlayer->Render();


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


void Game::playerCollisionUpdate(Player* player, BoxManager* box)
{
	//Collision
	FloatRect nextPos;//get players next position
	//for (auto &box : boxes)
	FloatRect playerBounds = player->getSprite().getGlobalBounds();
	//FloatRect playerBounds = serverPlayer->getPlayer()->getSprite().getGlobalBounds();
	FloatRect boxBounds = box->getSprite().getGlobalBounds();
	//nextPos = playerBounds;
	//nextPos.left += player->getVelocity().x;
	////nextPos.left += serverPlayer->getPlayer()->getVelocity().x;
	//nextPos.top += player->getVelocity().y;
	//nextPos.top += serverPlayer->getPlayer()->getVelocity().y;
	player->UpdateCollision(playerBounds, boxBounds);
	//serverPlayer->getPlayer()->UpdateCollision(playerBounds, boxBounds);
}

void Game::boxCollisionUpdate(Player* player, BoxManager* box)
{
	Vector2f newBoxPositionAddOn = player->getNewBoxPositionAddOn();
	//Vector2f newBoxPositionAddOn = serverPlayer->getPlayer()->getNewBoxPositionAddOn();
	box->setVelocity(newBoxPositionAddOn);
	//boxTest->Update(dt);

	player->setNewBoxPositionAddOn(sf::Vector2f(0.0f, 0.0f));
	//serverPlayer->getPlayer()->setNewBoxPositionAddOn(sf::Vector2f(0.0f, 0.0f));

	//sf::Vector2f boxPosition = box->getSprite().getPosition();
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