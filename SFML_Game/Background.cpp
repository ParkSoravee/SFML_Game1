#include "Background.h"

Background::Background(sf::Texture* texture, float speed)
{
	this->speed = speed;
	this->size = sf::Vector2f(1920.0f, 1080.0f);
	
	for (int i = 0; i < 2; i++)
	{
		body[i].setSize(size);
		body[i].setTexture(texture);
	}

	if(speed < 0)
	body[1].setPosition(size.x - 2.0f, 0.0f);
	else body[1].setPosition(-size.x + 2.0f, 0.0f);
}

void Background::Draw(sf::RenderWindow& window, float deltaTime)
{
	Update(deltaTime);
	for(int i=0;i<2;i++)
	window.draw(body[i]);
}

void Background::Update(float deltaTime)
{
	for (int i = 0; i < 2; i++)
	{
		position = body[i].getPosition();

		body[i].move(speed * deltaTime, 0);

		if (position.x <= -size.x && speed < 0)
			body[i].setPosition(size.x - 6.0f, position.y);
		else if (position.x >= size.x && speed > 0)
			body[i].setPosition(-size.x + 6.0f, position.y);
	}

}

