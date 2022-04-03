#include <SFML/Graphics.hpp>

class BoxManager
{
public:
	BoxManager(sf::RenderWindow* hwnd, sf::Vector2f position);
	~BoxManager();

	void Update(float dt);
	void Render();

	void MoveBox(sf::Vector2f velocity) { boxSprite.move(velocity); }

	sf::Sprite getSprite() { return boxSprite; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	sf::Vector2f getVelocity() { return velocity; }

	void setBoxPosition(sf::Vector2f position) { boxSprite.setPosition(position); }
	sf::Vector2f getBoxPosition() { return boxSprite.getPosition(); }

private:
	sf::RenderWindow* window;

	sf::Sprite boxSprite;
	sf::Texture boxTexture;

	sf::Vector2f velocity;


};

