#include "Enemy.h"

Enemy::Enemy(sf::Vector2f size)
{
	body.setSize(size);
	body.setPosition(1506.0f, 206.0f);
	body.setFillColor(sf::Color::Blue);
}

void Enemy::Update(float deltaTime)
{
	
}

void Enemy::Draw(sf::RenderWindow& window, float deltaTime)
{
	Update(deltaTime);
	window.draw(body);
}
