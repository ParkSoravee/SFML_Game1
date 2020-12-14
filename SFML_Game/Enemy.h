#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include "Bullet.h"

class Enemy
{
public:
	Enemy(int type, sf::Vector2f possition);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos);

	//--Collider
	Collider GetCollider() { return Collider(body); }
	void checkCollider(Collider temp);

	void hurt();
	unsigned int getHP() { return HP; }

private:
	sf::RectangleShape body;
	sf::Vector2f size;
	float speed = 0.0f;
	sf::Vector2f thisPos;
	sf::Vector2f playerPos;
	float timeForPoint = 0;
	float deltaY = 0;
	int type;
	unsigned int HP = 3;

	std::vector<Bullet> bullets;
	bool canShot = false;
	float shotDelay = 1;
	float shotDelayTime = 0;
	void setBull(int type);
	sf::Texture bullTex;
	float bullSpeed = 0;
	sf::Vector2f bullSize;
	unsigned int bullType = 0;
	sf::Vector2f possition;

};