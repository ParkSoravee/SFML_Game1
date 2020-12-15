#include "Item.h"

Item::Item(sf::Texture* texture, unsigned int type)
{
	this->type = type;
	this->speed = 50.0f;
}

void Item::Update(float deltaTime, sf::Vector2f playerPos)
{
}

void Item::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos)
{
}
