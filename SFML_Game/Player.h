#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Bullet.h"
#include <vector>
#include <iostream>
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	unsigned int colum;
	float speed;
	float switchTime;

	sf::Texture bullTexture;
	float delayTime = 0;
	std::vector<Bullet> bullets;
	bool canShot;
};

