#pragma once
#include <SFML/Graphics.hpp>

#include "NetworkMessages.h" //Used to update the score
#include "ObjectInterface.h"

//Inherits virtual class
class ScoreLine : public ObjectInterface
{
public:
	ScoreLine(sf::RenderWindow* hwnd); //Sets the score line and game text
	~ScoreLine();

	void setScoreLineText(int scoreRight, int scoreLeft);

	void Update(float dt) override;
	void Render() override;
	void Move(sf::Vector2f velocity) { scoreLine.move(velocity); }

	//Networking functions//
	sf::Packet createPacket() override; //ceates a packet to be sent through the network
	ObjectType getObjectType() override { return ObjectType::Score; }// used wehen sending packets
	MessageType getMessageType() override { return MessageType::Score; }//used when receiving packets

	int getID() override { return ID; }
	void setID(int ID) override { this->ID = ID; }

	void setBoxPosition(sf::Vector2f boxPosition) { this->boxPosition = boxPosition; } //used to calculate score

	//Not needed//
	//Had to be filled because of the virtual class but are not used by scoreline
	sf::Vector2f getVelocity() override { return sf::Vector2f(0, 0); }
	sf::Vector2f getPosition() override { return sf::Vector2f(0,0); }
	float getTimeSent() override { return 0; }
	int getAngle() override { return 0; }

private:

	sf::RenderWindow* window;

	sf::RectangleShape scoreLine;

	//Text Variables//
	sf::Font font;
	sf::Text titleText;
	sf::Text scoreTextLeft;
	sf::Text scoreTextRight;
	int scoreLeft = 0;
	int scoreRight = 0;

	int ID = 0;

	//uses box position for the score
	//if box is left of score line add 1 to score left, take 1 off score right
	//if box is right of score line add 1 to score right, take 1 off score left
	sf::Vector2f boxPosition;
};

