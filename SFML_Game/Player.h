#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Bullet.h"
#include "Collider.h"
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window, float deltaTime);
	bool checkCollider(Collider temp);
	
	unsigned int getHP() { return HP; };
	void reset();

	std::vector<Bullet> getBull() { return bullets; }

	//--Collider
	Collider GetCollider() { return Collider(body); }

	void hurt();

private:
	sf::RectangleShape body;
	Animation normalAnimation;
	Animation shotAnimation;
	unsigned int row;
	unsigned int colum;
	float speed;
	float switchTime;

	unsigned int HP = 3;

	float delayTime = 0;
	std::vector<Bullet> bullets;
	bool canShot;

	void setBull(int type);
	sf::Texture bullTex;
	float bullSpeed = 0;
	sf::Vector2f bullSize;
	unsigned int bullType = 0;
	
	bool canHurt = true;
	sf::Clock delay;

	sf::Sound shoot1;
	sf::SoundBuffer shootBuff;
};