#include "Bullet.h"

Bullet::Bullet(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f playerSize, float speed, unsigned int type)
{
	
	this->type = type;
	this->speed = speed;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	if (speed > 0)
		body.setPosition(position.x + size.x, position.y + 10.0f );
	else
		body.setPosition(position.x - size.x, position.y + 10.0f);
	
	if(type == 2)
		body.setPosition(1970, position.y);

	body.setTexture(texture);
	
}

void Bullet::Update(float deltaTime, sf::Vector2f playerPos)
{
	sf::Vector2f movement(0.0f, 0.0f);
	thisPos.y = body.getPosition().y;
	thisPos.x = body.getPosition().x;

	switch (type)
	{
	case 0:
		movement.x += speed;
		break;
	case 1:
		movement.x += speed;
		if (thisPos.x - playerPos.x > 300)
		{
			movement.y -= speed * ((playerPos.y > thisPos.y) - (playerPos.y < thisPos.y));
		}
		else
		{
			movement.y = 0;
		}
		
			break;
	case 2:
		movement.x += speed;
		break;

	default:
		break;
	}

	body.move(movement * deltaTime);

}

void Bullet::Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos)
{
	Update(deltaTime, playerPos);
	window.draw(body);
}

void Bullet::setDestroy(bool isDestroy)
{
	this->isDestroyBool = isDestroy;
}

bool Bullet::isOut()
{
	if (body.getPosition().x > 1920 + 150 || body.getPosition().x < 0 - 150)
		return true;
	return false;
}
