#pragma once
#include<SFML/Graphics.hpp>
class Background
{
public:
	Background(sf::Texture* texture, float speed);

	void Update(sf::RenderWindow& window);

private:
	sf::RectangleShape body[2];
	sf::Vector2f position;
	
	float speed;
	//unsigned int map;
};