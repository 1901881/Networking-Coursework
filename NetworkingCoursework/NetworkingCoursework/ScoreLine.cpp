#include "ScoreLine.h"

//Loads font and initialises text variables, also creates score line
ScoreLine::ScoreLine(sf::RenderWindow* hwnd)
{
	window = hwnd;

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

ScoreLine::~ScoreLine()
{
}

void ScoreLine::setScoreLineText(int scoreRight, int scoreLeft)
{
	std::string scoreStringRight = std::to_string(scoreRight);
	scoreTextRight.setString(scoreStringRight);

	std::string scoreStringLeft = std::to_string(scoreLeft);
	scoreTextLeft.setString(scoreStringLeft);
}

//Calculates score based off boxes position
void ScoreLine::Update(float dt)
{
	if (boxPosition.x > scoreLine.getOrigin().x)
	{
		scoreLeft = 0;
		scoreRight = 1;
	}
	else
	{
		scoreLeft = 1;
		scoreRight = 0;
	}

	setScoreLineText(scoreRight, scoreLeft);
}

void ScoreLine::Render()
{
	window->draw(titleText);
	window->draw(scoreTextLeft);
	window->draw(scoreTextRight);
	window->draw(scoreLine);
}

//Fills packet with the score data and message type
sf::Packet ScoreLine::createPacket()
{
	sf::Packet packet;

	packet << static_cast<int>(getMessageType()) << scoreLeft << scoreRight;

	return packet;
}
