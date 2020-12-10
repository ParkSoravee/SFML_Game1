#include "Status.h"

Status::Status(unsigned int score, unsigned int HP)
{
	this->score = score;
	this->HP = HP;

	sf::Font font1;
	font1.loadFromFile("./font/ERASBD.TTF");

	scoreText.setPosition(25, 15);
	scoreText.setFont(font1);
	scoreText.setFillColor(sf::Color(57, 57, 57, 255));
	scoreText.setString("Score:");
	scoreText.setCharacterSize(25);

	scoreShow.setPosition(55, 35);
	scoreShow.setFont(font1);
	scoreShow.setFillColor(sf::Color(57, 57, 57, 255));
	scoreShow.setString(std::to_string(score));
	scoreShow.setCharacterSize(70);
}

void Status::Update(unsigned int score, unsigned int HP)
{
	scoreShow.setString(std::to_string(score));
}

void Status::Draw(sf::RenderWindow& window, unsigned int score, unsigned int HP)
{
	Update(score, HP);

	//window.draw(scoreText);
	window.draw(scoreShow);
}
