#include "Enemy.h"

Enemy::Enemy(sf::Vector2f size, float speed, unsigned int type)
{
	//set anemy
	this->type = type;
	switch (type)
	{
	case 1:
		//size
		size = sf::Vector2f(150, 120);
		//texture

		//speed
		speed = 150.0f;
		//hp
		HP = 3;
		//bull type
		setBull(1);
		break;
	case 2:
		size = sf::Vector2f(150, 120);
		speed = 90.0f;
		HP = 4;
		setBull(2);
		break;
	}

	this->speed = speed;

	body.setSize(size); //--
	body.setPosition(1506.0f, 206.0f); //random with condition
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

void Enemy::checkCollider(Collider temp)
{
	//check Collider
	//--enemies bullet vs player
	for (Bullet& bullet : bullets)
	{
		if (bullet.GetCollider().CheckCollision(temp))
		{
			bullet.setDestroy(true);
			printf("Collider! from anemy\n");
		}
	}

	//--erase bull
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isDestroy() || bullets[i].isOut())
		{
			bullets.erase(bullets.begin() + i);
			printf("anemies bull erase\n");
		}
	}
}

void Enemy::setBull(int type)
{
	switch (type)
	{
	case 1:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet E.png");
		bullSize = sf::Vector2f(85.0f, 50.0f);
		bullSpeed = 600.0f;
		bullType = 0;
		shotDelay = 2;
		break;
	case 2:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet C.png");
		bullSize = sf::Vector2f(70.0f, 50.0f);
		bullSpeed = 400.0f;
		bullType = 0;
		shotDelay = 3;
		break;
	case 3:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet A.png");
		bullSize = sf::Vector2f(100.0f, 25.0f);
		bullSpeed = 1100.0f;
		bullType = 0;
		shotDelay = 4;
		break;
	case 4:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet B.png");
		bullSize = sf::Vector2f(70.0f, 70.0f);
		bullSpeed = 300.0f;
		bullType = 1; //follow
		shotDelay = 2;
		break;

	case 5: //a lot random
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet D.png");
		bullSize = sf::Vector2f(50.0f, 50.0f);
		bullSpeed = 300.0f;
		bullType = 2; //random a lot
		shotDelay = 7;
		break;

	case 6: //fire
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet F.png");
		bullSize = sf::Vector2f(140.0f, 120.0f);
		bullSpeed = 500.0f; //random??
		bullType = 4; //random a lot
		shotDelay = 7;
		break;

	default:
		break;
	}
}
