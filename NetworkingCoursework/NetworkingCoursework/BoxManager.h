#include <SFML/Graphics.hpp>
#include "ObjectInterface.h"

//Inherits virtual class
class BoxManager : public ObjectInterface
{
public:
	BoxManager(sf::RenderWindow* hwnd, sf::Vector2f position);	//Sets the box up
	~BoxManager();

	void Update(float dt) override;
	void Render() override;//Draws the box onto the screen

	void Move(sf::Vector2f velocity) { boxSprite.move(velocity); }

	int getID() override { return ID; }
	void setID(int ID) override { this->ID = ID; }

	//Networking functions//
	sf::Packet createPacket() override; //ceates a packet to be sent through the network
	ObjectType getObjectType() override { return ObjectType::Box; }// used wehen sending packets
	MessageType getMessageType() override { return MessageType::Box; }//used when receiving packets
	sf::Sprite getSprite() { return boxSprite; };

	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	void setBoxPosition(sf::Vector2f position) { boxSprite.setPosition(position); }

	//Not needed//
	//Had to be filled because of the virtual class but are not used by the box manager
	sf::Vector2f getVelocity() override { return velocity; }
	sf::Vector2f getPosition() override { return boxSprite.getPosition(); }
	float getTimeSent() override { return 0; }
	int getAngle() override { return 0; }

private:
	sf::RenderWindow* window;

	sf::Sprite boxSprite;
	sf::Texture boxTexture;

	sf::Vector2f velocity;

	int ID = 0;
};

