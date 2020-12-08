#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	normalAnimation(texture, imageCount, switchTime),
	shotAnimation(texture, imageCount, 0.15f)
{
	this->speed = speed;
	this->switchTime = switchTime;
	row = 0;
	colum = 8;
	canShot = true;

	body.setSize(sf::Vector2f(170.0f, 140.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);

}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && body.getPosition().x > 0)
		movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && body.getPosition().x < 1920 - body.getSize().x)
		movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && body.getPosition().y > 0)
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && body.getPosition().y < 1080 - body.getSize().y)
		movement.y += speed * deltaTime;

	//---- Bullet
	this->delayTime += deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->delayTime > 0.5)
	{
		canShot = false;
		printf("shot!\n");
		this->bullets.push_back(Bullet(bullTexture(0), sf::Vector2f(70.0f, 50.0f), body.getPosition(), body.getSize(), 600.0f)); //speed positive = player
		this->delayTime = 0;
	}
	if (delayTime > 3.0f * 0.15f/*showSwitchTime*/) //delay for shot
		canShot = true;

	//----

	if (!canShot)
	{
		shotAnimation.Update(1, deltaTime, 3);
		body.setTextureRect(shotAnimation.uvRect);
	}
	else
	{
		normalAnimation.Update(0, deltaTime, 8);
		body.setTextureRect(normalAnimation.uvRect);
	}

	//animation.Update(row, deltaTime, colum);
	//body.setTextureRect(animation.uvRect);
	body.move(movement);

}

void Player::Draw(sf::RenderWindow& window, float deltaTime)
{
	Update(deltaTime);
	window.draw(body);

	for (Bullet& bullet : this->bullets)
		bullet.Draw(window, deltaTime);
}

void Player::checkCollider(Collider temp)
{
	//check Collider
	
	for (Bullet& bullet : bullets)
	{
		if (bullet.GetCollider().CheckCollision(temp))
		{
			bullet.setDestroy(true);
			printf("Collider!\n");
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isDestroy() || bullets[i].isOut() )
		{
			bullets.erase(bullets.begin() + i);
			printf("erase\n");
		}
	}
}

sf::Texture* Player::bullTexture(int type)
{
	switch (type)
	{
	case 0:
		bullTex.loadFromFile("./sprite/Bullets/Hero Bullet C.png");
		break;
	case 1:
		bullTex.loadFromFile("./sprite/Bullets/Hero Bullet A.png");
		break;
	default:
		break;
	}
	
	return &bullTex;
}
