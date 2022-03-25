#include <SFML/Graphics.hpp>

class BoxManager
{
public:
	BoxManager(sf::RenderWindow* hwnd, sf::Vector2f position);
	~BoxManager();

	void Update(float dt);
	void Render();
	sf::Sprite getSprite() { return boxSprite; };

private:
	sf::RenderWindow* window;

	sf::Sprite boxSprite;
	sf::Texture boxTexture;


};

