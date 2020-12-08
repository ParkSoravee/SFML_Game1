#include "Enemy.h"

Enemy::Enemy(sf::Vector2f size, float speed)
{
	this->speed = speed;

	body.setSize(size);
	body.setPosition(1506.0f, 206.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setFillColor(sf::Color::Blue);
}

void Enemy::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	timeForPoint += deltaTime;
	thisPos.y = body.getPosition().y;

	/*if (timeForPoint > 1.5f)
	{
		thisPos.y = body.getPosition().y;
		timeForPoint = 0;
	}*/

	deltaY = playerPos.y - thisPos.y;

	if (deltaY > 0)
	{
		movement.y += speed * deltaTime;
	}
	else if (deltaY < 0)
	{
		movement.y -= speed * deltaTime;
	}
	else
	{
		movement.y = 0;
	}
	
	//printf("%f\n", thisPos.y);
	body.move(movement);
}

void Enemy::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos)
{
	this->playerPos = playerPos;
	Update(deltaTime);
	window.draw(body);
}
