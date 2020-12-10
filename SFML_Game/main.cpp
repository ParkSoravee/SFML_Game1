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

	//----Bullet
	/*sf::Texture bullTexture;
	if (!bullTexture.loadFromFile("./sprite/Bullets/Hero-Bullet-C.png"))
		printf("load not completed");*/

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
		//loop for: for all enemies
		Collider temp = enemyTest.GetCollider();
		player.checkCollider(temp);

		window.clear();

		for (Background& background : backgrounds)
			background.Draw(window, deltaTime);

		player.Draw(window, deltaTime);

		enemyTest.Draw(window, deltaTime, player.getPosition());

		window.draw(scoreText);
		window.draw(scoreShow);
		window.display();
	}
	return 0;
}