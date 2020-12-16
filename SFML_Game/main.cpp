#define _CRT_SECURE_NO_WARNINGS
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

enum stateGame{MAINMENUSTATE = 0, GAMESTATE, GAMEOVERSTATE, HIGHSCORESTATE};
void showText(sf::Vector2f position, std::string word, sf::Font* font, int size, sf::RenderWindow& window);

int main()
{
	//state game
	sf::Clock gameTime;
	bool canSpawn = true;
	int GAMEPLAYSTATE = 0;
	int n = 0;
	int kill = 0;
	//---

	srand(time(NULL));
	sf::Vector2f position;

	unsigned state = MAINMENUSTATE;

	//score
	unsigned int score = 0;
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
	
	
	//--- spite
	sf::Texture enemyTex[6];
	enemyTex[0].loadFromFile("./sprite/enemy1.png");
	enemyTex[1].loadFromFile("./sprite/enemy2.png");
	enemyTex[2].loadFromFile("./sprite/enemy3.png");
	enemyTex[3].loadFromFile("./sprite/enemy4.png");
	/*enemyTex[4].loadFromFile("");
	enemyTex[5].loadFromFile("");*/

	Player player(&playerTexture, sf::Vector2u(8, 6), 0.2f, 550.0f);
	//Player player(&playerTexture, sf::Vector2u(8, 6), 0.2f, 550.0f);
	//float randomY = fmod(rand(), 500.0f);

	//----

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

	//Text box
	sf::RectangleShape object;
	object.setSize(sf::Vector2f(300.0f, 70.0f));
	object.setOrigin(sf::Vector2f(150.0f, 35.0f));
	object.setFillColor(sf::Color(122, 122,122, 111));
	object.setPosition(sf::Vector2f(window.getSize().x / 2, 440.0f)); // Edit here

	sf::RectangleShape cursor;
	cursor.setSize(sf::Vector2f(5.0f, 64.0f));
	cursor.setOrigin(sf::Vector2f(2.5f, 32.0f));
	cursor.setPosition(sf::Vector2f(655, 450.0f)); // Edit here
	cursor.setFillColor(sf::Color::Black);

	float totalTime = 0;
	sf::Clock clock;
	//bool state = false;

	char last_char = ' ';

	std::string input;
	input = "";

	sf::Text playerName;
	playerName.setFont(font1);
	playerName.setCharacterSize(40);
	playerName.setFillColor(sf::Color::White);
	
	playerName.setPosition(object.getPosition().x - 130, object.getPosition().y - 25);

	//HIGHSCORE
	std::vector<std::pair<int, std::string>> highScore;
	FILE* file;
	char temp[25];
	std::string nameArr[6];
	int scoreArr[6];
	bool collectHS = false;
	file = fopen("./highScore.txt", "r");
	for (int i = 0; i < 5; i++) {
		fscanf(file, "%s", temp);
		nameArr[i] = temp;
		fscanf(file, "%d", &scoreArr[i]);
		highScore.push_back(std::make_pair(scoreArr[i], nameArr[i]));
	}
	//---- 

	float deltaTime = 0.0f;

	window.setFramerateLimit(120);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Vector2i mouse = sf::Mouse::getPosition();
		sf::Vector2f mousePosition = sf::Vector2f(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

		if (state == MAINMENUSTATE)
		{
			sf::Event event;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

			
			Button Newgame(840, 520 , 250, 50, &font1, "NEW GAME", 40,
				sf::Color(122, 122, 122, 255), sf::Color(122, 122, 122, 122), sf::Color(255, 255, 255, 0));
			Button HighScore(840, 620, 250, 50, &font1, "HIGHSCORE", 40,
				sf::Color(122, 122, 122, 255), sf::Color(122, 122, 122, 122), sf::Color(255, 255, 255, 0));
			Button Exit(840, 720, 250, 50, &font1, "EXIT", 40,
				sf::Color(122, 122, 122, 255), sf::Color(122, 122, 122, 122), sf::Color(255, 255, 255, 0));

			Newgame.update(mousePosition);
			HighScore.update(mousePosition);
			Exit.update(mousePosition);


			//text box

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			if (event.type == sf::Event::EventType::TextEntered)
			{
				if (last_char != event.text.unicode && event.text.unicode == 13 &&
					input.length() > 0) // delete
				{

					state = GAMESTATE;

				}
				else if (last_char != event.text.unicode && event.text.unicode == 8 &&
					input.length() > 0) // delete
				{

					last_char = event.text.unicode;
					input.erase(input.length() - 1);
					playerName.setString(input);
					cursor.setPosition(650.0f + playerName.getGlobalBounds().width + 5, 450.0f);
					std::cout << input << std::endl;

				}
				else if (last_char != event.text.unicode &&
					(event.text.unicode >= 'a' && event.text.unicode <= 'z' ||
						event.text.unicode >= 'A' && event.text.unicode <= 'Z' ||
						event.text.unicode >= '0' && event.text.unicode <= '9'))
				{
					//std::cout << event.text.unicode << std::endl;
					last_char = event.text.unicode;

					input += event.text.unicode;

					playerName.setString(input);

					cursor.setPosition(650.0f + playerName.getGlobalBounds().width + 5, 450.0f);

					std::cout << input << std::endl;
				}

			}

			if (event.type == sf::Event::EventType::KeyReleased && last_char != ' ')
			{
				last_char = ' ';
			}

			

			//DRAW
			for (Background& background : backgrounds)
				background.Draw(window, deltaTime);

			window.draw(object);
			window.draw(playerName);


			Newgame.render(&window);
			HighScore.render(&window);
			Exit.render(&window);
			if (Newgame.isPressed())
			{
				ready = true;
				state = GAMESTATE;
			}
			if (HighScore.isPressed())
			{
				ready = true;
				state = HIGHSCORESTATE;
			}
			if (Exit.isPressed())
			{
				window.close();
			}

			showText(sf::Vector2f(660.0f, 950.0f), "63010952 Soravee Rattanaapha", &font1, 40, window);
			
		}
		else if (state == HIGHSCORESTATE)
		{
			if (ready == true)
			{


				highScore.erase(highScore.begin(), highScore.end());
				file = fopen("./highScore.txt", "r");
				for (int i = 0; i < 5; i++) {
					fscanf(file, "%s", temp);
					nameArr[i] = temp;
					fscanf(file, "%d", &scoreArr[i]);
					highScore.push_back(std::make_pair(scoreArr[i], nameArr[i]));
				}
				ready = false;
			}
				Button Back(840, 920, 250, 50, &font1, "BACK", 40,
					sf::Color(122, 122, 122, 255), sf::Color(122, 122, 122, 122), sf::Color(255, 255, 255, 0));


				Back.update(mousePosition);

				//DRAW
				for (Background& background : backgrounds)
					background.Draw(window, deltaTime);
				Back.render(&window);
				
				showText(sf::Vector2f(700.0f, 395.0f), highScore[0].second, &font1, 40, window);
				showText(sf::Vector2f(1100.0f, 395.0f), std::to_string(highScore[0].first), &font1, 40, window);
				showText(sf::Vector2f(700.0f, 445.0f), highScore[1].second, &font1, 40, window);
				showText(sf::Vector2f(1100.0f, 445.0f), std::to_string(highScore[1].first), &font1, 40, window);
				showText(sf::Vector2f(700.0f, 495.0f), highScore[2].second, &font1, 40, window);
				showText(sf::Vector2f(1100.0f, 495.0f), std::to_string(highScore[2].first), &font1, 40, window);
				showText(sf::Vector2f(700.0f, 545.0f), highScore[3].second, &font1, 40, window);
				showText(sf::Vector2f(1100.0f, 545.0f), std::to_string(highScore[3].first), &font1, 40, window);
				showText(sf::Vector2f(700.0f, 595.0f), highScore[4].second, &font1, 40, window);
				showText(sf::Vector2f(1100.0f, 595.0f), std::to_string(highScore[4].first), &font1, 40, window);
		
				if (Back.isPressed())
				{
					state = MAINMENUSTATE;
					ready = true;
				}
		}
		else if (state == GAMESTATE)
		{
			if (ready == true)
			{
			
				/*position.x = 1300.0f + fmod(rand(), 500.0f);
				position.y = player.getPosition().y;

				enemies.push_back(Enemy(5, position));
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

				position.x = 1300.0f + fmod(rand(), 500.0f);
				for (int i = 0; i < enemies.size(); i++)
				{
					if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
						position.x = 1300.0f + fmod(rand(), 500.0f);
				}
				enemies.push_back(Enemy(4, position));

				std::cout << enemies.size() << std::endl;*/
				gameTime.restart();
				player.reset();
				ready = false;
			}
			//game state --------------------
			//printf("%f\n", gameTime.getElapsedTime().asSeconds());
			switch (GAMEPLAYSTATE)
			{
			case 0:
				if (gameTime.getElapsedTime().asSeconds() >= 2.0f)
				{
					canSpawn = true;
					gameTime.restart();
				}
				if (canSpawn == true)
				{
					canSpawn = false;
					switch (n) 
					{
					case 0:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[0], sf::Vector2u(8, 3), 0.2f, 1, position));
						n++;
						break;
					case 1:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[0], sf::Vector2u(8, 3), 0.2f, 1, position));
						n++;
						break;
					case 2:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[1], sf::Vector2u(8, 3), 0.2f, 2, position));
						n++;
						break;
					case 3:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[1], sf::Vector2u(8, 3), 0.2f, 2, position));
						n++;
						break;
					
					}
				}
				//printf("%d\n", kill);
				if (n == kill)
				{
					printf("next\n");
					n = 0;
					kill = 0;
					GAMEPLAYSTATE++;
					canSpawn = true;
				}
				break;
			case 1: 
				printf("1");
				if (gameTime.getElapsedTime().asSeconds() >= 2.0f)
				{
					canSpawn = true;
					gameTime.restart();
				}
				if (canSpawn == true)
				{
					canSpawn = false;
					switch (n)
					{
					case 0:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[2], sf::Vector2u(8, 3), 0.2f, 3, position));
						n++;
						break;
					case 1:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[1], sf::Vector2u(8, 3), 0.2f, 2, position));
						n++;
						break;
					case 2:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[1], sf::Vector2u(8, 3), 0.2f, 2, position));
						n++;
						break;
					case 3:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[0], sf::Vector2u(8, 3), 0.2f, 1, position));
						n++;
						break;

					}
				}
				if (n == kill)
				{
					printf("next\n");
					n = 0;
					kill = 0;
					GAMEPLAYSTATE++;
					canSpawn = true;
				}
				break;
			case 2:
				printf("2");
				if (gameTime.getElapsedTime().asSeconds() >= 2.0f)
				{
					canSpawn = true;
					gameTime.restart();
				}
				if (canSpawn == true)
				{
					canSpawn = false;
					switch (n)
					{
					case 0:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[1], sf::Vector2u(8, 3), 0.2f, 2, position));
						n++;
						break;
					case 1:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[2], sf::Vector2u(8, 3), 0.2f, 3, position));
						n++;
						break;
					case 2:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[2], sf::Vector2u(8, 3), 0.2f, 3, position));
						n++;
						break;
					case 3:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[3], sf::Vector2u(8, 3), 0.2f, 4, position));
						n++;
						break;

					}
				}
				if (n == kill)
				{
					printf("next\n");
					n = 0;
					kill = 0;
					GAMEPLAYSTATE++;
					canSpawn = true;
				}
				break;
			case 3:
				printf("3");
				if (gameTime.getElapsedTime().asSeconds() >= 1.2f)
				{
					canSpawn = true;
					gameTime.restart();
				}
				if (canSpawn == true)
				{
					canSpawn = false;
					switch (n)
					{
					case 0:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[3], sf::Vector2u(8, 3), 0.2f, 4, position));
						n++;
						break;
					case 1:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[3], sf::Vector2u(8, 3), 0.2f, 4, position));
						n++;
						break;
					case 2:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[2], sf::Vector2u(8, 3), 0.2f, 3, position));
						n++;
						break;
					case 3:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[1], sf::Vector2u(8, 3), 0.2f, 2, position));
						n++;
						break;
					case 4:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						for (int i = 0; i < enemies.size(); i++)
						{
							if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
								position.x = 1300.0f + fmod(rand(), 500.0f);
						}
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[0], sf::Vector2u(8, 3), 0.2f, 1, position));
						n++;
						break;
					}
				}
				if (n == kill)
				{
					printf("next\n");
					n = 0;
					kill = 0;
					GAMEPLAYSTATE++;
					canSpawn = true;
				}
				break;
			case 4:
				printf("4");
				if (gameTime.getElapsedTime().asSeconds() >= 1.2f)
				{
					canSpawn = true;
					gameTime.restart();
				}
				if (canSpawn == true)
				{
					canSpawn = false;
					switch (n)
					{
					case 0:
						position.x = 1300.0f + fmod(rand(), 500.0f);
						position.y = player.getPosition().y;
						enemies.push_back(Enemy(&enemyTex[4], sf::Vector2u(8, 3), 0.2f, 5, position));
						n++;
						break;
					
					}
				}
				if (n == kill)
				{
					printf("next\n");
					n = 0;
					kill = 0;
					GAMEPLAYSTATE++;
					canSpawn = true;
				}

				break;
			default: // random * boss
				printf("5");
				if (gameTime.getElapsedTime().asSeconds() >= 2.0f)
				{
					canSpawn = true;
					gameTime.restart();
				}
				if (canSpawn && n < 6)
				{
					canSpawn = false;
					position.x = 1300.0f + fmod(rand(), 500.0f);
					for (int i = 0; i < enemies.size(); i++)
					{
						if (position.x >= enemies[i].getPosition().x - enemies[i].getSize().x && position.x <= enemies[i].getPosition().x + enemies[i].getSize().x)
							position.x = 1300.0f + fmod(rand(), 500.0f);
					}
					position.y = player.getPosition().y;
					unsigned int temp = 1 + rand() % 4;
					enemies.push_back(Enemy(&enemyTex[temp], sf::Vector2u(8, 3), 0.2f, temp, position));
					n++;
				}

				if (n == kill)
				{
					printf("next\n");
					n = 0;
					kill = 0;
					GAMEPLAYSTATE++;
					canSpawn = true;
				}
				break;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) player.reset();
			//--------------------------------------

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
						kill++;
						score += enemies[i].getScore();
						enemies.erase(enemies.begin() + i);
						printf("%d\n", score);
					}

				}
				else if (enemies[i].getPosition().x < -200)
				{
					kill++;
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
			scoreShow.setString(std::to_string(score));
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

			if (!collectHS) {
				highScore.erase(highScore.begin(), highScore.end());
				file = fopen("./highScore.txt", "r");
				for (int i = 0; i < 5; i++) {
					fscanf(file, "%s", temp);
					nameArr[i] = temp;
					fscanf(file, "%d", &scoreArr[i]);
					highScore.push_back(std::make_pair(scoreArr[i], nameArr[i]));
				}
				/*if (playerName == "") {
					playerName = "NoName";
				}*/
				
				highScore.push_back(std::make_pair(score, input));
				std::sort(highScore.begin(), highScore.end());
				fclose(file);
				file = fopen("./highScore.txt", "w");
				char temp[26];
				for (int i = 5; i >= 1; i--) {
					strcpy(temp, highScore[i].second.c_str());
					fprintf(file, "%s %d\n", temp, highScore[i].first);
				}
				fclose(file);
				collectHS = true;
			}

			
			Button Menu(840, 920, 250, 50, &font1, "EXIT", 40,
				sf::Color(122, 122, 122, 255), sf::Color(122, 122, 122, 122), sf::Color(255, 255, 255, 0));

			Menu.update(mousePosition);
			//DRAW
			for (Background& background : backgrounds)
				background.Draw(window, deltaTime);

			Menu.render(&window);

			showText(sf::Vector2f(600.0f, 150.0f), "GAME OVER!", &font1, 120, window);
			showText(sf::Vector2f(760.0f, 390.0f), "Your Score", &font1, 80, window);
			showText(sf::Vector2f(830.0f, 515.0f), std::to_string(score), &font1, 100, window);
			if (Menu.isPressed())
			{
				window.close();
			}
		}
		window.display();
		
	}
	return 0;
}

void showText(sf::Vector2f position, std::string word, sf::Font* font, int size, sf::RenderWindow& window) {
	sf::Text text;
	text.setFont(*font);
	text.setPosition(position);
	text.setString(word);
	text.setCharacterSize(size);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3);
	window.draw(text);
}