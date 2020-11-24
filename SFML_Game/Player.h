#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Bullet.h"
#include "Collider.h"
#include <vector>
#include <iostream>
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);
	
	std::vector<Bullet> getBull() { return bullets; }

	//--Collider
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation normalAnimation;
	Animation shotAnimation;
	unsigned int row;
	unsigned int colum;
	float speed;
	float switchTime;

	sf::Texture bullTexture;
	float delayTime = 0;
	std::vector<Bullet> bullets;
	bool canShot;
};

