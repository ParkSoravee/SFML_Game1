#include "Background.h"

Background::Background(sf::Texture* texture, float speed)
{
	this->speed = speed;
	this->size = sf::Vector2f(1920.0f, 1080.0f);
	
	body[0].setSize(size);
	body[0].setTexture(texture);
	body[1].setSize(size);
	body[1].setTexture(texture);
	if(speed < 0)
	body[1].setPosition(body[1].getPosition().x + size.x - 2.0f , 0.0f);
	else body[1].setPosition(body[1].getPosition().x - size.x + 2.0f, 0.0f);
}

void Background::Update(sf::RenderWindow& window)
{
	float sizeX = body[0].getSize().x;
	for (int i = 0; i < 2; i++)
	{
		position = body[i].getPosition();

		body[i].setPosition(position.x += speed, position.y); // -0.05
		//body[i].move(speed, 0); // -0.05

		if (position.x <= -sizeX)
			body[i].setPosition(sizeX - 4.0f, position.y);
			//body[i].setPosition(sizeX, position.y);
		else if(position.x >= sizeX)
			body[i].setPosition(-sizeX + 4.0f, position.y);
			//body[i].setPosition(-sizeX, position.y);
	}
	window.draw(body[0]);
	window.draw(body[1]);
}

