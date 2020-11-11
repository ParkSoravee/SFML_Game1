#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;

	body.setSize(sf::Vector2f(170.0f, 140.0f));
	//body.setOrigin(body.getSize() / 2.0f);
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

	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
	}

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

	//---- Bullet
	this->delayTime += deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->delayTime > 1)
	{
		printf("shot!\n");
		this->bullets.push_back(Bullet(0, sf::Vector2f(50.0f, 50.0f), body.getPosition(), 300.0f)); //speed positive = player
		this->delayTime = 0;
	}

}

void Player::Draw(sf::RenderWindow& window, float deltaTime)
{
	Update(deltaTime);
	window.draw(body);

	for (Bullet& bullet : this->bullets)
		bullet.Draw(window, deltaTime);
}
