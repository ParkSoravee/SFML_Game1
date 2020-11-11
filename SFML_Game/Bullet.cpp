#include "Bullet.h"

Bullet::Bullet(unsigned int bullTex, sf::Vector2f size, sf::Vector2f position, float speed)
{
	this->speed = speed;

	body.setSize(size);
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	sf::Texture bullTexture;
	if (!bullTexture.loadFromFile("./sprite/Bullets/Hero-Bullet-C.png"))
		printf("load not completed");
	
	/*switch (bullTex)
	{
	case 0:
		bullTexture.loadFromFile("./sprite/Bullets/Hero Bullet C.png");
		printf("\nloaded");
	default:
		break;
	}*/
	body.setTexture(&bullTexture);
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
