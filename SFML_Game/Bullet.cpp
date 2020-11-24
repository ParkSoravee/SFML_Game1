#include "Bullet.h"

Bullet::Bullet(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f playerSize, float speed)
{
	this->speed = speed;
	body.setSize(size);
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position.x + (2 * size.x) + 20.0f, position.y + (size.y / 2.0f) + 30.0f);
	
	
	/*switch (bullTex)
	{
	case 0:
		bullTexture.loadFromFile("./sprite/Bullets/Hero Bullet C.png");
		printf("\nloaded");
	default:
		break;
	}*/

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