#include <SFML/Graphics.hpp>

class BoxManager
{
public:
	BoxManager(sf::RenderWindow* hwnd, sf::Vector2f position);
	~BoxManager();

	void Update(float dt);
	void Render();
	sf::Sprite getSprite() { return boxSprite; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }

private:
	sf::RenderWindow* window;

	sf::Sprite boxSprite;
	sf::Texture boxTexture;

	sf::Vector2f velocity;


};

