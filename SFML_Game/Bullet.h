#pragma once
#include <SFML\Graphics.hpp>
class Bullet
{
public:
	Bullet(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f playerSize, float speed);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);

private:
	sf::RectangleShape body;
	float speed;
};