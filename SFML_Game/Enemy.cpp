#include "Enemy.h"

Enemy::Enemy(sf::Vector2f size, float speed, unsigned int type)
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

	//movement.y = speed * ( (playerPos.y > thisPos.y)-(playerPos.y < thisPos.y) );

	deltaY = playerPos.y - thisPos.y;

	if (deltaY > 0)
	{
		movement.y += speed;
	}
	else if (deltaY < 0)
	{
		movement.y -= speed;
	}
	/*else
	{
		movement.y = 0;
	}*/
	
	//printf("%f\n", thisPos.y);
	body.move(movement * deltaTime);

	//Shot
	if (canShot == true)
	{
		canShot = false;
		printf("enemy shot!\n");
		setBull(0);
		this->bullets.push_back(Bullet(&bullTex, bullSize, body.getPosition(), body.getSize(), -bullSpeed, bullType)); //speed positive = player
	}

	shotDelayTime += deltaTime;
	if (shotDelayTime >= shotDelay)
	{
		canShot = true;
		shotDelayTime = 0;
	}
	
}

void Enemy::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos)
{
	this->playerPos = playerPos;
	Update(deltaTime);
	window.draw(body);

	for (Bullet& bullet : this->bullets)
		bullet.Draw(window, deltaTime);
}

void Enemy::setBull(int type)
{
	switch (type)
	{
	case 0:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet E.png");
		bullSize = sf::Vector2f(85.0f, 50.0f);
		bullSpeed = 600.0f;
		bullType = 0;
		break;
	case 1:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet A.png");
		bullSize = sf::Vector2f(100.0f, 25.0f);
		bullSpeed = 1100.0f;
		bullType = 0;
		break;
	default:
		break;
	}
}
