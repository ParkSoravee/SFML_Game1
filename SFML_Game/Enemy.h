#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"

class Enemy
{
public:
	Enemy(sf::Vector2f size);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);

	//--Collider
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;

};

