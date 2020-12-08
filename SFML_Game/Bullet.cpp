#include "Bullet.h"

Bullet::Bullet(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f playerSize, float speed, unsigned int type)
{
	
		
	this->speed = speed;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	if (speed > 0)
		body.setPosition(position.x + size.x, position.y + 10.0f );
	else
		body.setPosition(position.x - size.x, position.y + 10.0f);
	
	body.setTexture(texture);

}

void Bullet::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	movement.x += speed * deltaTime;

	body.move(movement);

}

void Bullet::Draw(sf::RenderWindow& window, float deltaTime)
{
	Update(deltaTime);
	window.draw(body);
}

void Bullet::setDestroy(bool isDestroy)
{
	this->isDestroyBool = isDestroy;
}

bool Bullet::isOut()
{
	if (body.getPosition().x > 1920)
		return true;
	return false;
}
