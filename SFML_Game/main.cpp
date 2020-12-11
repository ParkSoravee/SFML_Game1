#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "Background.h"

#define SC_Width 1080
#define SC_Height 1920

int main()
{
	//score
	unsigned int score = 952;
	bool isGameRun = 0;

	//text
	sf::Font font1;
	font1.loadFromFile("./font/ERASBD.TTF");

	sf::Text scoreText;
	scoreText.setPosition(25, 15);
	scoreText.setFont(font1);
	scoreText.setFillColor(sf::Color(57, 57, 57, 255));
	scoreText.setString("Score:");
	scoreText.setCharacterSize(25);

	sf::Text scoreShow;
	scoreShow.setPosition(55, 35);
	scoreShow.setFont(font1);
	scoreShow.setFillColor(sf::Color(57, 57, 57, 255));
	scoreShow.setString(std::to_string(score));
	scoreShow.setCharacterSize(70);
	
	//buttom Status
	sf::Texture playerMini;
	sf::RectangleShape playerMiniBody;
	playerMini.loadFromFile("./sprite/status/mini-1.png");
	playerMiniBody.setTexture(&playerMini);
	playerMiniBody.setPosition(15, 1020);
	playerMiniBody.setSize(sf::Vector2f(90, 60));
	//heart
	sf::RectangleShape heart[3];
	sf::Texture heartTex;
	heartTex.loadFromFile("./sprite/status/heart.png");
	for (int i=0;i<3;i++)
	{
		heart[i].setTexture(&heartTex);
		heart[i].setSize(sf::Vector2f(60, 60));
		heart[i].setPosition(130 + (63 * i) , 1020);
	}


	//
	sf::RenderWindow window(sf::VideoMode(SC_Height, SC_Width), "PARK's GAME", sf::Style::Fullscreen);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("./sprite/eagle01.png");

	Player player(&playerTexture, sf::Vector2u(8, 6), 0.2f, 550.0f);

	//-----Enemy
	Enemy enemyTest(sf::Vector2f(150,120), 150.0f, 1);

	//----Background
	sf::Texture bgTexture1[5];
	bgTexture1[0].loadFromFile("./sprite/bg/bg1/Sky.png");
	bgTexture1[1].loadFromFile("./sprite/bg/bg1/mountainA.png");
	bgTexture1[2].loadFromFile("./sprite/bg/bg1/mountainB.png");
	bgTexture1[3].loadFromFile("./sprite/bg/bg1/cloud.png");
	bgTexture1[4].loadFromFile("./sprite/bg/bg1/land2.png");

	std::vector<Background> backgrounds;
	backgrounds.push_back(Background(&bgTexture1[0], -50.0f));
	backgrounds.push_back(Background(&bgTexture1[1], -100.0f));
	backgrounds.push_back(Background(&bgTexture1[2], -150.0f));
	backgrounds.push_back(Background(&bgTexture1[3], 100.0f));
	backgrounds.push_back(Background(&bgTexture1[4], -150.0f));

	float deltaTime = 0.0f;
	sf::Clock clock;
	window.setFramerateLimit(120);

	while (window.isOpen())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
		deltaTime = clock.restart().asSeconds();

		/*if (deltaTime > 1.0f / 30.0f)
			deltaTime = 1.0f / 30.0f;*/

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		//check collider playerBullet and enemy
		
		Collider temp1 = enemyTest.GetCollider();
		player.checkCollider(temp1);

		//loop for: for all enemies
		Collider temp2 = player.GetCollider();
		enemyTest.checkCollider(temp2);

		window.clear();

		for (Background& background : backgrounds)
			background.Draw(window, deltaTime);

		player.Draw(window, deltaTime);

		enemyTest.Draw(window, deltaTime, player.getPosition());

		//top Status
		window.draw(scoreText);
		window.draw(scoreShow);

		//buttom Status
		window.draw(playerMiniBody);
		for (int i = 0; i < player.getHP(); i++)
		{
			window.draw(heart[i]);
		}
		

		window.display();
	}
	return 0;
}