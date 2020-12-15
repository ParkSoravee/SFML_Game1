#include "Enemy.h"

Enemy::Enemy(int type, sf::Vector2f position)
{
	
	//set anemy
	this->type = type;
	this->position = position;

	switch (type)
	{
	case 1:
		//possition

		//size
		size = sf::Vector2f(150, 120);
		//texture
		body.setFillColor(sf::Color::Blue);
		//speed
		speed = 200.0f;
		//hp
		HP = 4;
		//bull type
		setBull(1);
		//score set
		score = 300;
		break;
	case 2:
		size = sf::Vector2f(150, 120);
		body.setFillColor(sf::Color::Red);
		speed = 160.0f;
		HP = 4;
		setBull(2);
		score = 400;
		break;
	case 3:
		size = sf::Vector2f(150, 120);
		body.setFillColor(sf::Color::Green);
		speed = 150.0f;
		HP = 5;
		setBull(3);
		score = 500;
		break;
	case 4:
		size = sf::Vector2f(150, 120);
		body.setFillColor(sf::Color::Magenta);
		speed = 200.0f;
		HP = 5;
		setBull(4);
		score = 700;
		break;
	case 5:
		size = sf::Vector2f(150*3, 120*3);
		body.setFillColor(sf::Color::Cyan);
		speed = 90.0f;
		HP = 20;
		setBull(5);
		score = 2000;
		break;
	case 6:
		size = sf::Vector2f(150, 120);
		body.setFillColor(sf::Color::Yellow);
		speed = 400.0f;
		HP = 7;
		setBull(6);
		score = 1000;
		break;
	}

	body.setSize(size); //--
	body.setPosition( 2000, 100 + (rand() % 900) ); //random with condition
	body.setOrigin(body.getSize() / 2.0f);
	/*body.setFillColor(sf::Color::Blue);*/
}

void Enemy::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	timeForPoint += deltaTime;
	thisPos.y = body.getPosition().y;
	thisPos.x = body.getPosition().x;

	/*if (timeForPoint > 1.5f)
	{
		thisPos.y = body.getPosition().y;
		timeForPoint = 0;
	}*/
	//float delta_posX = possition.x - body.getPosition().x;
	//float delta_posY = ;

	switch (type)
	{
	case 1 :
		if (delay1.getElapsedTime().asSeconds() >= 2)
		{
			tempY = playerPos.y;
			delay1.restart();
		}
		movement.y += speed * ((tempY > thisPos.y) - (tempY < thisPos.y));
		
		if (position.x < thisPos.x)
			movement.x -= speed;
	break;
	case 2 :
		
		if (thisPos.x > 1920.0f / 2.0f)
		{
			movement.x -= speed;
			movement.y += speed * ((playerPos.y > thisPos.y) - (playerPos.y < thisPos.y));
		}
		else
		{
			delay2 += deltaTime;
			if (delay2 >= 1)
			{
				speed = 550.0f;
				movement.x -= speed;
				movement.y = 0;
			}
			break;
	case 3:
		//position.x = rand();
		if (position.x < thisPos.x)
		{
			movement.x -= speed;
		}
		movement.y += speed * ((position.y > thisPos.y) - (position.y < thisPos.y));
		
		if (delay1.getElapsedTime().asSeconds() > 4)
		{
			position.y = 150 + rand() % 600;
			delay1.restart();
		}
		break;
	case 4:
		movement.x += speed * ((position.x > thisPos.x) - (position.x < thisPos.x));
		movement.y += speed * ((position.y > thisPos.y) - (position.y < thisPos.y));
		if (delay1.getElapsedTime().asSeconds() > 4)
		{
			position.x = 900 + rand() % 750;
			position.y = 100 + rand() % 700;
			delay1.restart();
		}
		break;
	case 5:
		movement.x += speed * ((position.x > thisPos.x) - (position.x < thisPos.x));
		movement.y += speed * ((position.y > thisPos.y) - (position.y < thisPos.y));
		if (delay1.getElapsedTime().asSeconds() > 4)
		{
			position.x = 1300 + rand() % 300;
			position.y = 400 + rand() % 200;
			delay1.restart();
		}
		break;
			
	case 6:
		movement.x += speed * ((position.x > thisPos.x) - (position.x < thisPos.x));
		movement.y += speed * ((position.y > thisPos.y) - (position.y < thisPos.y));
		if (delay1.getElapsedTime().asSeconds() > 6.5)
		{
			position.x = 1300 + rand() % 300;
			position.y = 400 + rand() % 200;
			delay1.restart();
		}
		break;
		}
		
	}

	body.move(movement * deltaTime);

	//Shot
	
	if (type == 5 && canShot == true)
	{
		if (delay3.getElapsedTime().asSeconds() >= 0.3)
		{
			count++;
			this->bullets.push_back(Bullet(&bullTex, bullSize, sf::Vector2f(1120.0f, 50 + rand() % 850) , body.getSize(), -bullSpeed, bullType));
			delay3.restart();
		}
		if (count >= 11) canShot = false;
	}
	else if (canShot == true)
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
		count = 0;
	}
	
}

void Enemy::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos)
{
	this->playerPos = playerPos;
	Update(deltaTime);
	window.draw(body);

	for (Bullet& bullet : this->bullets)
		bullet.Draw(window, deltaTime, playerPos);
}

bool Enemy::checkCollider(Collider temp)
{
	//--erase bull
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isDestroy() || bullets[i].isOut())
		{
			bullets.erase(bullets.begin() + i);
			printf("anemies bull erase\n");
		}
	}
	//check Collider
	//--enemies bullet vs player
	for (Bullet& bullet : bullets)
	{
		if (bullet.GetCollider().CheckCollision(temp))
		{
			bullet.setDestroy(true);
			printf("Collider! from anemy\n");
			return true;
		}
	}

	return false;
}

void Enemy::hurt()
{
	printf("Ouchh!!\n");
	HP--;
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
		shotDelay = 1.5;
		break;
	case 2:
		bullTex.loadFromFile("./sprite/Bullets/Villain Bullet C.png");
		bullSize = sf::Vector2f(70.0f, 50.0f);
		bullSpeed = 300.0f;
		bullType = 0;
		shotDelay = 4;
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
		shotDelay = 4;
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
		bullSize = sf::Vector2f(170.0f, 150.0f);
		bullSpeed = 700.0f; //random??
		bullType = 0; //
		shotDelay = 6.5;
		break;

	default:
		break;
	}
}
