#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"
#include "Bullet.h"
#include "Animation.h"
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int type, sf::Vector2f possition);

	sf::Vector2f getPosition() { return body.getPosition(); }
	sf::Vector2f getSize() { return size; }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime, sf::Vector2f playerPos);

	//--Collider
	Collider GetCollider() { return Collider(body); }
	bool checkCollider(Collider temp);

	void hurt();
	unsigned int getHP() { return HP; }

	int getScore() { return score; }

private:
	sf::RectangleShape body;
	sf::Vector2f size;

	Animation normalAnimation;
	Animation shotAnimation;
	unsigned int row;
	unsigned int colum;
	float switchTime = 0.2f;
	sf::Texture* texture;
	sf::Vector2u imageCount;
	bool canAnShot = false;
	sf::Clock delayAn;

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
	sf::Vector2f position;

	float delay2 = 0;
	sf::Clock delay1;
	sf::Clock delay3;
	int count = 0;
	int score = 0;
	float tempY;

	sf::Sound enemy3;
	sf::SoundBuffer enemy3Buff;
};