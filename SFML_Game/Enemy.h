#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include "Bullet.h"

class Enemy
{
public:
	Enemy(sf::Vector2f size, float speed, unsigned int type);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos);

	//--Collider
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	float speed;
	sf::Vector2f thisPos;
	sf::Vector2f playerPos;
	float timeForPoint = 0;
	float deltaY = 0;
	
};