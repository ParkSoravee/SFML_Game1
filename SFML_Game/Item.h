#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
class Item
{
public:
	Item(sf::Texture* texture, unsigned int type);

	void Update(float deltaTime, sf::Vector2f playerPos);
	void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos);
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	sf::Texture texture;
	float speed;
	unsigned int type;
	
};

