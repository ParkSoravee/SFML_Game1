#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
class Bullet
{
public:
	Bullet(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f playerSize, float speed, unsigned int type);

	void Update(float deltaTime, sf::Vector2f playerPos);
	void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos);

	void setDestroy(bool isDestroy);
	bool isDestroy() { return isDestroyBool; }
	bool isOut();

	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	sf::Texture texture;
	float speed;
	sf::Vector2f thisPos;

	bool isDestroyBool = false;
	unsigned int type;
};