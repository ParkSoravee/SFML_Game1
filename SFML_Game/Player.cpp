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
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);

	
	if (!bullTexture.loadFromFile("./sprite/Bullets/Hero-Bullet-C.png"))
		printf("load bull not completed");

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
		this->bullets.push_back(Bullet(&bullTexture, sf::Vector2f(70.0f, 50.0f), body.getPosition(), body.getSize(), 600.0f)); //speed positive = player
		this->delayTime = 0;
	}
	if (delayTime > 3.0f * 0.15f/*showSwitchTime*/)
		canShot = true;
	//----

	if (!canShot)
	{
		row = 1;
		colum = 3;
		shotAnimation.Update(row, deltaTime, colum);
		body.setTextureRect(shotAnimation.uvRect);
	}
	else
	{
		row = 0;
		colum = 8;
		normalAnimation.Update(row, deltaTime, colum);
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
