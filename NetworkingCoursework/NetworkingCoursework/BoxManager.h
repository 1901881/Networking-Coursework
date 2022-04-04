#include <SFML/Graphics.hpp>

#include "ObjectInterface.h"

class BoxManager : public ObjectInterface
{
public:
	BoxManager(sf::RenderWindow* hwnd, sf::Vector2f position);
	~BoxManager();

	void Update(float dt) override;
	void Render() override;

	void Move(sf::Vector2f velocity) { boxSprite.move(velocity); }

	int getID() override { return ID; }
	void setID(int ID) override { this->ID = ID; }

	sf::Packet createPacket() override;
	ObjectType getObjectType() override { return ObjectType::Box; }
	MessageType getMessageType() override { return MessageType::Box; }


	sf::Sprite getSprite() { return boxSprite; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }


	void setBoxPosition(sf::Vector2f position) { boxSprite.setPosition(position); }
	sf::Vector2f getBoxPosition() { return boxSprite.getPosition(); }

	//Not needed//
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

