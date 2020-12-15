#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "Background.h"
#include "Button.h"

#define SC_Width 1080
#define SC_Height 1920

enum stateGame{MAINMENUSTATE = 0, GAMESTATE, GAMEOVERSTATE};

int main()
{

	srand(time(NULL));
	sf::Vector2f position;

	unsigned state = MAINMENUSTATE;

	//score
	unsigned int score = 952;
	bool isGameRun = 0;

	bool ready = true;

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
		heart[i].setPosition(130.0f + (63.0f * i) , 1020.0f);
	}


	//
	sf::RenderWindow window(sf::VideoMode(SC_Height, SC_Width), "PARK's GAME", sf::Style::Fullscreen);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("./sprite/eagle01.png");

	

	//-----Enemy
	//Enemy enemyTest(sf::Vector2f(150,120), 150.0f, 1);
	std::vector<Enemy> enemies;
	//possition = ( player.getPosition().x, player.getPosition().y );
	
	Player player(&playerTexture, sf::Vector2u(8, 6), 0.2f, 550.0f);
	//Player player(&playerTexture, sf::Vector2u(8, 6), 0.2f, 550.0f);
	//float randomY = fmod(rand(), 500.0f);
	
	


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
	backgrounds.push_back(Background(&bgTexture1[3], -25.0f));
	backgrounds.push_back(Background(&bgTexture1[4], -150.0f));

	float deltaTime = 0.0f;
	sf::Clock clock;
	window.setFramerateLimit(120);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Vector2i mouse = sf::Mouse::getPosition();
		sf::Vector2f mousePosition = sf::Vector2f(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

		if (state == MAINMENUSTATE)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

			
			Button Newgame(900, 500 , 250, 50, &font1, "NEW GAME", 40,
				sf::Color(122, 122, 122, 255), sf::Color(122, 122, 122, 122), sf::Color(255, 255, 255, 0));

			Newgame.update(mousePosition);





			//DRAW
			for (Background& background : backgrounds)
				background.Draw(window, deltaTime);

			Newgame.render(&window);
			if (Newgame.isPressed())
			{
				ready = true;
				state = GAMESTATE;
			}
			
		}
		else if (state == GAMESTATE)
		{
			if (ready == true)
			{
			
				position.x = 1300.0f + fmod(rand(), 500.0f);
				position.y = player.getPosition().y;

				enemies.push_back(Enemy(1, position));

				position.x = 1300.0f + fmod(rand(), 500.0f);
				for (int i = 0; i < enemies.size(); i++)
				{
					if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
						position.x = 1300.0f + fmod(rand(), 500.0f);
				}
				enemies.push_back(Enemy(2, position));

				position.x = 1300.0f + fmod(rand(), 500.0f);
				for (int i = 0; i < enemies.size(); i++)
				{
					if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
						position.x = 1300.0f + fmod(rand(), 500.0f);
				}
				enemies.push_back(Enemy(3, position));

				std::cout << enemies.size() << std::endl;
				

				player.reset();

				ready = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
			//deltaTime = clock.restart().asSeconds();

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

			for (int i = 0; i < enemies.size(); i++)
			{
				Collider temp1 = enemies[i].GetCollider();

				if (player.checkCollider(temp1))
				{
					enemies[i].hurt();
					if (enemies[i].getHP() <= 0)
					{
						enemies.erase(enemies.begin() + i);
					}

				}
				if (enemies[i].getPosition().x < -200)
				{
					std::cout << enemies.size() << std::endl;
					enemies.erase(enemies.begin() + i);
					printf("Erase enemies\n");
				}

			}

			//check collider playerBullet to enemies

			for (int i = 0; i < enemies.size(); i++)
			{
				Collider temp2 = player.GetCollider();
				if (enemies[i].checkCollider(temp2))
				{
					player.hurt();
				}
			}

			if (player.getHP() <= 0)
			{
				
				for (int i = 0; i < enemies.size(); i++)
				{
					std::cout << enemies.size() << std::endl;
					enemies.erase(enemies.begin());
					printf("i = %d\n", i);
				}
				
				std::cout << "Enemy = " << enemies.size() << std::endl;
				
				if(enemies.size() == 0)
					state = GAMEOVERSTATE;
			}

			window.clear();

			for (Background& background : backgrounds)
				background.Draw(window, deltaTime);

			player.Draw(window, deltaTime);

			//enemy draw
			for (Enemy& enemy : enemies)
				enemy.Draw(window, deltaTime, player.getPosition());

			//top Status
			window.draw(scoreText);
			window.draw(scoreShow);

			//buttom Status
			window.draw(playerMiniBody);

			for (unsigned int i = 0; i < player.getHP(); i++)
			{
				window.draw(heart[i]);
			}

		}
		else if (state == GAMEOVERSTATE)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					window.close();
					break;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				ready = true;
				state = MAINMENUSTATE;
			}
			//DRAW
			for (Background& background : backgrounds)
				background.Draw(window, deltaTime);
		}
		window.display();

	}
	return 0;
}