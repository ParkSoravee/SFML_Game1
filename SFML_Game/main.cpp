#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Background.h"

#define SC_Width 1080
#define SC_Height 1920

int main()
{
	sf::RenderWindow window(sf::VideoMode(SC_Height, SC_Width), "PARK's GAME", sf::Style::Fullscreen);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("./sprite/eagle01.png");

	Player player(&playerTexture, sf::Vector2u(8, 6), 0.2f, 350.0f);

	sf::Texture bgTexture1[5];
	bgTexture1[0].loadFromFile("./sprite/bg/bg1/Sky.png");
	bgTexture1[1].loadFromFile("./sprite/bg/bg1/mountainA.png");
	bgTexture1[2].loadFromFile("./sprite/bg/bg1/mountainB.png");
	bgTexture1[3].loadFromFile("./sprite/bg/bg1/cloud.png");
	bgTexture1[4].loadFromFile("./sprite/bg/bg1/land2.png");
	Background background(&bgTexture1[0], -1.0f);
	Background background1(&bgTexture1[1], -1.0f);
	Background background2(&bgTexture1[2], -1.5f);
	Background background3(&bgTexture1[3], 1.0f);
	Background background4(&bgTexture1[4], -1.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;
	window.setFramerateLimit(72);

	while (window.isOpen())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
		deltaTime = clock.restart().asSeconds();

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
		
		player.Update(deltaTime);
		window.clear();
		background.Update(window);
		background1.Update(window);
		background2.Update(window);
		background3.Update(window);
		background4.Update(window);

		player.Draw(window);

		window.display();
	}
	return 0;
}