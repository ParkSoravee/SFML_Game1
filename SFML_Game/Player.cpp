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
	body.setPosition(450.0f, 500.0f);
	body.setTexture(texture);

}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && body.getPosition().x > 0 + body.getSize().x / 2)
		movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && body.getPosition().x < 1920 - body.getSize().x / 2)
		movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && body.getPosition().y > 0 + body.getSize().y / 2)
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && body.getPosition().y < 1080 - body.getSize().y)
		movement.y += speed * deltaTime;

	//---- Bullet
	this->delayTime += deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->delayTime > 0.5)
	{
		canShot = false;
		printf("shot!\n");
		setBull(1);
		this->bullets.push_back(Bullet(&bullTex, bullSize, body.getPosition(), body.getSize(), bullSpeed, bullType)); //speed positive = player
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

bool Player::checkCollider(Collider temp)
{
	//check Collider
	
	//--erase bull
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isDestroy() || bullets[i].isOut())
		{
			bullets.erase(bullets.begin() + i);
			printf("player bull erase\n");
		}
	}
	//--player bullet vs anemies
	for (Bullet& bullet : bullets)
	{
		if (bullet.GetCollider().CheckCollision(temp))
		{
			bullet.setDestroy(true);
			printf("Collider! from player\n");
			return true;
		}
	}
	
	return false;
}

void Player::setBull(int type)
{
	switch (type)
	{
	case 1:
		bullTex.loadFromFile("./sprite/Bullets/Hero Bullet C.png");
		bullSize = sf::Vector2f(70.0f, 50.0f);
		bullSpeed = 600.0f;
		bullType = 0;
		break;
	case 2:
		bullTex.loadFromFile("./sprite/Bullets/Hero Bullet A.png");
		bullSize = sf::Vector2f(100.0f, 25.0f);
		bullSpeed = 1100.0f;
		bullType = 0;
		break;
	default:
		break;
	}
}