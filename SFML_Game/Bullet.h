#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
class Bullet
{
public:
	Bullet(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f playerSize, float speed);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);

	void setDestroy(bool isDestroy);
	bool isDestroy() { return isDestroyBool; }
	bool isOut();

	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	float speed;

	bool isDestroyBool = false;
};