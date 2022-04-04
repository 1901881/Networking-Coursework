#pragma once
#include <SFML/Graphics.hpp>


#include "NetworkMessages.h"
#include "ObjectInterface.h"

class ScoreLine : public ObjectInterface
{
public:
	ScoreLine(sf::RenderWindow* hwnd);
	~ScoreLine();

	void setScoreLineText(int scoreRight, int scoreLeft);

	void Update(float dt) override;
	void Render() override;
	void Move(sf::Vector2f velocity) { scoreLine.move(velocity); }

	sf::Packet createPacket() override;
	ObjectType getObjectType() override { return ObjectType::Score; }
	MessageType getMessageType() override { return MessageType::Score; }

	int getID() override { return ID; }
	void setID(int ID) override { this->ID = ID; }

	void setBoxPosition(sf::Vector2f boxPosition) { this->boxPosition = boxPosition; }

	//Not needed//
	sf::Vector2f getVelocity() override { return sf::Vector2f(0, 0); }
	sf::Vector2f getPosition() override { return sf::Vector2f(0,0); }
	float getTimeSent() override { return 0; }
	int getAngle() override { return 0; }

private:

	sf::RenderWindow* window;

	sf::RectangleShape scoreLine;

	sf::Font font;
	sf::Text titleText;
	sf::Text scoreTextLeft;
	sf::Text scoreTextRight;

	int scoreLeft = 0;
	int scoreRight = 0;

	int ID = 0;

	sf::Vector2f boxPosition;
};

