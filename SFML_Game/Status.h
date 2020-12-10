#pragma once
#include <SFML/Graphics.hpp>

class Status
{
public:
	Status(unsigned int score, unsigned int HP);

	void Update(unsigned int score, unsigned int HP);
	void Draw(sf::RenderWindow& window, unsigned int score, unsigned int HP);

private:
	unsigned int score;
	unsigned int HP;
	sf::Text scoreText;
	sf::Text scoreShow;

};

