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


	if (!font.loadFromFile("media/RetroGaming.ttf"))
	{
		//handle error
	}
	titleText.setFont(font);
	titleText.setString("Box Pusher");
	titleText.setFillColor(sf::Color::White);
	titleText.setCharacterSize(25);


	std::string scoreStringLeft = std::to_string(scoreLeft);
	scoreTextLeft.setFont(font);
	scoreTextLeft.setString(scoreStringLeft);
	scoreTextLeft.setFillColor(sf::Color::White);
	scoreTextLeft.setCharacterSize(35);
	scoreTextLeft.setPosition(window->getSize().y / 2 + 30, 0);

	std::string scoreStringRight = std::to_string(scoreRight);
	scoreTextRight.setFont(font);
	scoreTextRight.setString(scoreStringRight);
	scoreTextRight.setFillColor(sf::Color::White);
	scoreTextRight.setCharacterSize(35);
	scoreTextRight.setPosition(window->getSize().y / 2 + 120, 0);
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
	
	sf::Vector2f boxPosition = boxTest->getSprite().getPosition();
	//sf::Vector2f screenSize = sf::Vector2f(window->getSize().y / 2.0f);

	if (boxTest->getSprite().getPosition().x > scoreLine.getOrigin().x)
	{
		scoreLeft = 0;
		scoreRight = 1;
	}
	else
	{
		scoreLeft = 1;
		scoreRight = 0;
	}

	std::string scoreStringRight = std::to_string(scoreRight);
	scoreTextRight.setString(scoreStringRight);

	std::string scoreStringLeft = std::to_string(scoreLeft);
	scoreTextLeft.setString(scoreStringLeft);
	
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

	window->draw(titleText);
	window->draw(scoreTextLeft);
	window->draw(scoreTextRight);
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