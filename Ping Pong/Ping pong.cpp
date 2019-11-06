//Ping pong

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

//Scoring system
int main()
{
	int score = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong");
	sf::Event event;
	sf::RectangleShape player1(sf::Vector2f(10.f, 100.f)), player2(sf::Vector2f(10.f, 100.f));
	sf::CircleShape ball(20.f);
	sf::Font font;
	font.loadFromFile("D:/Games/C++ games/Ping Pong/Ping Pong/arial.ttf");
	sf::Text gameovertext("GAME OVER!", font, 30);
	sf::Text scoring("Score - ", font, 30);
	float x = 5.f, y = 5.f;
	sf::Vector2f velocity(x, y);
	enum cases
	{
		NONE,
		UPPERBOUND,
		LOWERBOUND,
		RIGHTBOUND,
		LEFTBOUND, 
		OUTOFBOUNDS
	};
	cases ballcase = cases::NONE;
	ball.setFillColor(sf::Color::Green);
	player1.setFillColor(sf::Color::Blue);
	player2.setFillColor(sf::Color::Red);
	player1.setPosition(sf::Vector2f(10.f, 300.f));
	player2.setPosition(sf::Vector2f(780.f, 300.f));
	ball.setPosition(400.f, 300.f);
	scoring.setPosition(sf::Vector2f(650.f, 0.f));
	while (window.isOpen())
	{
		sf::Text s(reinterpret_cast<char*>(score), font, 30);
		s.setPosition(sf::Vector2f(650.f, 0.f));
		ball.move(velocity);
		if (ball.getPosition().y >= 570.f)
		{
			ballcase = cases::LOWERBOUND;
		}
		else if (ball.getPosition().y <= 0.f)
		{
			ballcase = cases::UPPERBOUND;
		}
		else if (ball.getPosition().x <= player1.getGlobalBounds().left + 10.f &&
			ball.getPosition().y >= player1.getGlobalBounds().top - 20.f &&
			ball.getPosition().y <= player1.getGlobalBounds().top + player1.getGlobalBounds().height + 20.f)
		{
			score++;
			ballcase = cases::LEFTBOUND;
		}
		else if (ball.getPosition().x >= player2.getGlobalBounds().left - 45.f &&
			ball.getPosition().y >= player2.getGlobalBounds().top - 20.f&&
			ball.getPosition().y <= player2.getGlobalBounds().top + player2.getGlobalBounds().height + 20.f)
		{
			ballcase = cases::RIGHTBOUND;
		}
		else if(ball.getPosition().x <= 0.0f || ball.getPosition().x >= 800.f)
		{
			score--;
			ballcase = cases::OUTOFBOUNDS;
		}
		switch (ballcase)
		{
			case UPPERBOUND :
			{
				y = 5.f;
				velocity = sf::Vector2f(x, y);
				break;
			}
			case LOWERBOUND :
			{
				y = -5.f;
				velocity = sf::Vector2f(x, y);
				break;
			}
			case LEFTBOUND :
			{
				x = 5.f;
				velocity = sf::Vector2f(x, y);
				score++;
				break;
			}
			case RIGHTBOUND :
			{
				x = -5.f;
				velocity = sf::Vector2f(x, y);
				break;
			}
			case OUTOFBOUNDS:
			{
				sf::RenderWindow gameoverwindow(sf::VideoMode(800, 600), "Game Over!");
				window.close();
				sf::Event goevent;
				while (gameoverwindow.isOpen())
				{
					gameoverwindow.display();
					gameoverwindow.clear();
					gameoverwindow.draw(gameovertext);
					while (gameoverwindow.pollEvent(goevent))
					{
						if (goevent.type == sf::Event::Closed)
							gameoverwindow.close();
					}
				}
			}
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player1.getPosition().y >= 10)
			{
				player1.move(0.f, -20.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player1.getPosition().y <= 490)
			{
				player1.move(0.f, 20.0f);
			}
		}
		if (velocity.y < 0 && player2.getPosition().y >= 10)
		{
			player2.move(0.f, -5.f);
		}
		if (velocity.y > 0 && player2.getPosition().y <= 490)
		{
			player2.move(0.f, 5.f);
		}
		window.display();
		window.clear();
		window.draw(player1);
		window.draw(player2);
		window.draw(ball);
		window.draw(scoring);
		window.draw(s);
	}
	scoring.setString("Score - " + score);
	string temp = scoring.getString();
	cout << temp;
	return 0;
}

