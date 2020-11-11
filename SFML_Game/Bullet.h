#pragma once
#include <SFML\Graphics.hpp>
class Bullet
{
public:
	Bullet(unsigned int bullTex, sf::Vector2f size, sf::Vector2f position, float speed);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);

private:
	sf::RectangleShape body;
	float speed;

	//sf::Texture bullTexture;
};

