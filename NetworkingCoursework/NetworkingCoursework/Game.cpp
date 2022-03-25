#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	// Set window and input for the Gameulation
	this->window = window;

	serverPlayer = new ServerPlayer(window);

	for (int i = 0; i < boxAmount; i++) {
		sf::Vector2f boxPosition = sf::Vector2f(i * 70, i * 70);
		//boxManager[i] = new BoxManager(window, boxPosition);
		BoxManager* box = new BoxManager(window, boxPosition);
		boxes.push_back(box);
	}
	
	boxTest = new BoxManager(window, sf::Vector2f(300, 300));

	//init road line
	scoreLine.setSize(sf::Vector2f(5.0f, window->getSize().y));
	scoreLine.setOrigin(sf::Vector2f((window->getSize().x) / 2.0f, 0.0f));
	scoreLine.setPosition(sf::Vector2f(window->getSize().x, 0.0f));

}

Game::~Game()
{
	
}

void Game::update(float dt)
{
	
	//Collision
	FloatRect nextPos;//get players next position
	
	//for (auto &box : boxes)

	FloatRect playerBounds = serverPlayer->getSprite().getGlobalBounds();
	FloatRect boxBounds = boxTest->getSprite().getGlobalBounds();

	

	nextPos = playerBounds;
	nextPos.left += serverPlayer->getVelocity().x;
	nextPos.top += serverPlayer->getVelocity().y;


	serverPlayer->UpdateCollision(playerBounds, boxBounds);


	
	
	
	
	


	//////////////////
	serverPlayer->Update(dt);
	Vector2f newBoxPositionAddOn = serverPlayer->getNewBoxPositionAddOn();
	boxTest->setVelocity(newBoxPositionAddOn);
	boxTest->Update(dt);

	serverPlayer->setNewBoxPositionAddOn(sf::Vector2f(0.0f, 0.0f));
	


	
}


void Game::render(float dt)
{
	beginDraw();
	window->draw(scoreLine);
	
	//for (int i = 0; i < boxAmount; i++) {
	//	//boxManager[i]->Render();
	//}

	//for (auto& box : boxes)
	//{
	//	box->Render();
	//}

	boxTest->Render();
	serverPlayer->Render();

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