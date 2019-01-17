﻿#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "ship.h"
#include "utility.h"

typedef sf::Vector2<float> Vector2;

sf::Font font;

const std::string gameName = "Space Gosciniak";

class projectile
{
	sf::Texture _texture;
	Vector2 _speed;

public:
	Vector2 _pos;
	sf::Sprite _sprite;
	projectile(sf::Texture tex, Vector2 pos, Vector2 speed) : _texture(tex), _pos(pos), _speed(speed)
	{
		_sprite.setTexture(_texture);
		_sprite.setPosition(_pos);
	}

	void addToVector(std::vector<sf::Drawable*>& vect)
	{
		vect.push_back(&_sprite);
	}

	void update()
	{
		_pos += _speed;
		_sprite.setPosition(_pos);
	}
};

int menu(sf::RenderWindow& window)
{
	std::vector<sf::Drawable*> vect;
	std::vector<button*> bvect;
	sf::Texture bgMenuT;
	bgMenuT.loadFromFile("../img/bg_menu.png");
	sf::Sprite bgMenu;
	bgMenu.setTexture(bgMenuT);
	vect.push_back(&bgMenu);
	button b1(Vector2(300, 225), "Play", Vector2(200, 75), vect);
	button b2(Vector2(300, 350), "Credits", Vector2(200, 75), vect);
	button b3(Vector2(300, 475), "Quit", Vector2(200, 75), vect);
	bvect.push_back(&b1);
	bvect.push_back(&b2);
	bvect.push_back(&b3);
	sf::Text logo;
	logo = sf::Text(gameName, font, 70);
	logo.setStyle(sf::Text::Bold);
	logo.setPosition((window.getSize().x - logo.getLocalBounds().width - logo.getLocalBounds().left) / 2, 75);
	logo.setFillColor(sf::Color(0, 0, 0, 255));
	logo.setOutlineColor(sf::Color(255, 255, 255, 255));
	logo.setOutlineThickness(4);
	vect.push_back(&logo);
	cursor c1 = cursor(Vector2(0, 0), vect);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return -2;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				for (std::vector<button*>::iterator it = bvect.begin(); it != bvect.end(); it++)
				{
					if (event.mouseButton.x >= (*it)->_pos.x && event.mouseButton.x <= (*it)->_pos.x + (*it)->_size.x && event.mouseButton.y >= (*it)->_pos.y && event.mouseButton.y <= (*it)->_pos.y + (*it)->_size.y)
					{
						if ((*it)->_txt == "Quit")
						{
							window.close();
							return -2;
						}
						if ((*it)->_txt == "Credits")
						{
							return 1;
						}
						if ((*it)->_txt == "Play")
						{
							return 2;
						}
					}

				}
			}
		}
		c1.render(false);
		for (std::vector<button*>::iterator it = bvect.begin(); it != bvect.end(); it++)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2 bPos = (*it)->_pos;
			if (mousePos.x >= bPos.x && mousePos.x <= bPos.x + (*it)->_size.x && mousePos.y >= bPos.y && mousePos.y <= bPos.y + (*it)->_size.y)
			{
				c1.setPos(Vector2(bPos.x - 25, bPos.y + 30));
				c1.render(true);
				break;
			}
		}
		window.clear();
		for (std::vector<sf::Drawable*>::iterator it = vect.begin(); it != vect.end(); it++)
			window.draw(**it);
		window.display();
	}
	return 0;
}

int credits(sf::RenderWindow& window)
{
	std::vector<sf::Drawable*> vect;
	std::ifstream creditsFile;
	creditsFile.open("../credits.txt", std::ifstream::in);
	std::string creditsStr, temp;
	std::vector<sf::Text*> Tvect;
	std::vector<std::string> Svect;
	float y = 75;
	while (!creditsFile.eof())
	{
		std::getline(creditsFile, temp);
		Svect.push_back(temp);
	}
	sf::Texture bgMenuT;
	bgMenuT.loadFromFile("../img/bg_menu.png");
	sf::Sprite bgMenu;
	bgMenu.setTexture(bgMenuT);
	vect.push_back(&bgMenu);
	for (auto it = Svect.begin(); it != Svect.end(); it++)
	{
		auto tmp = new sf::Text;
		tmp->setString(*it);
		tmp->setFont(font);
		tmp->setCharacterSize(20);
		tmp->setFillColor(sf::Color(0, 0, 0, 255));
		tmp->setOutlineColor(sf::Color(255, 255, 255, 255));
		tmp->setOutlineThickness(1.5);
		tmp->setPosition((window.getSize().x - tmp->getLocalBounds().width - tmp->getLocalBounds().left) / 2, y);
		y += tmp->getLocalBounds().height + tmp->getLocalBounds().top + 5;
		Tvect.push_back(tmp);
		vect.push_back(tmp);
	}
	std::vector<button*> bvect;
	button b1(Vector2(300, 475), "Back", Vector2(200, 75), vect);
	bvect.push_back(&b1);
	cursor c1 = cursor(Vector2(0, 0), vect);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return -2;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				for (std::vector<button*>::iterator it = bvect.begin(); it != bvect.end(); it++)
				{
					if (event.mouseButton.x >= (*it)->_pos.x && event.mouseButton.x <= (*it)->_pos.x + (*it)->_size.x && event.mouseButton.y >= (*it)->_pos.y && event.mouseButton.y <= (*it)->_pos.y + (*it)->_size.y)
					{
						if ((*it)->_txt == "Back")
						{
							for (auto it = Tvect.begin(); it != Tvect.end(); it++)
								delete *it;
							return 0;
						}
						std::cout << (*it)->_txt << "\n";
					}
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			return 0;
		}
		c1.render(false);
		for (std::vector<button*>::iterator it = bvect.begin(); it != bvect.end(); it++)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2 bPos = (*it)->_pos;
			if (mousePos.x >= bPos.x && mousePos.x <= bPos.x + (*it)->_size.x && mousePos.y >= bPos.y && mousePos.y <= bPos.y + (*it)->_size.y)
			{
				c1.setPos(Vector2(bPos.x - 25, bPos.y + 30));
				c1.render(true);
				break;
			}
		}
		window.clear();
		for (std::vector<sf::Drawable*>::iterator it = vect.begin(); it != vect.end(); it++)
			window.draw(**it);
		window.display();
	}
	return 0;
}

int game(sf::RenderWindow& window)
{
	const float speedChange = 0.2f;
	std::vector<sf::Drawable*> vect;
	sf::Texture bgGameTex;
	bgGameTex.loadFromFile("../img/bg_game0.jpg");
	sf::Sprite bgGame;
	bgGame.setTexture(bgGameTex);
	std::vector<sf::Texture> playerTextures;
	std::list<projectile*> playerProjectiles;
	std::list<enemy*> evect;
	sf::Texture playerProjectileTex;
	playerProjectileTex.loadFromFile("../img/player_proc.png");
	for (int i = 0; i < 5; i++)
	{
		sf::Texture tex;
		tex.loadFromFile("../img/player_spritesheet.png", sf::IntRect(i * 41, 0, 41, 52));
		playerTextures.push_back(tex);
	}
	int shot = 0;
	player Player(playerTextures, Vector2(400, 500), vect);
	std::list<projectile*> enemyProjectiles;
	std::vector<sf::Texture> enemyTextures;
	sf::Texture enemyProjectileTex;
	enemyProjectileTex.loadFromFile("../img/enemy_proc.png");
	for (int i = 0; i < 5; i++)
	{
		sf::Texture tex;
		tex.loadFromFile("../img/enemy1.png", sf::IntRect(i * 35, 0, 35, 48));
		enemyTextures.push_back(tex);
	}
	enemy Enemy(enemyTextures, Vector2(100, 100), vect);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Player.changeSpeed(Vector2(speedChange*-1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Player.changeSpeed(Vector2(speedChange, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Player.changeSpeed(Vector2(0, speedChange*-1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Player.changeSpeed(Vector2(0, speedChange));
		}
		if (shot==1)
		{
			playerProjectiles.push_back(new projectile(playerProjectileTex, Vector2(Player._pos.x+12,Player._pos.y), Vector2(Player._speed.x, Player._speed.y - 0.5)));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		{
			shot++;
			shot %= 2048;
		}
		else
		{
			shot = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return 0;
		}
		window.clear();
		window.draw(bgGame);
		Player.update();
		Enemy.update();
		for (auto it = playerProjectiles.begin(); it != playerProjectiles.end();)
		{
			(*it)->update();
			if ((*it)->_pos.y < 0)
			{
				delete (*it);
				it = playerProjectiles.erase(it);
			}
			else
			{
				window.draw((*it)->_sprite);
				it++;
			}

		}
		for (auto it = evect.begin(); it != evect.end(); it++) {
			if (Player._pos.x + 41 > (*it)->_pos.x&& Player._pos.x < (*it)->_pos.x + 35)
			{
				(*it)->shot++;
				(*it)->shot %= 2048;
			}
			if((*it)->shot==1)
			{
				enemyProjectiles.push_back(new projectile(playerProjectileTex, Vector2((*it)->_pos.x + 12, (*it)->_pos.y), Vector2((*it)->_speed.x, (*it)->_speed.y + 0.5)));
			}
		}
		for (auto it = enemyProjectiles.begin(); it != enemyProjectiles.end();)
		{
			(*it)->update();
			if ((*it)->_pos.y < 0)
			{
				delete (*it);
				it = enemyProjectiles.erase(it);
			}
			else
			{
				window.draw((*it)->_sprite);
				it++;
			}

		}
		for (std::vector<sf::Drawable*>::iterator it = vect.begin(); it != vect.end(); it++)
			window.draw(**it);
		window.display();
	}
	return 0;
}

int main()
{
	font.loadFromFile("../arial.ttf");
	int state = 0;																	// 0 - menu, 1 - gra, 2 - credits, -1 błąd, -2 zamknij
	sf::RenderWindow window(sf::VideoMode(800, 600), gameName);
	sf::Clock clock;
	while (state >= 0)
	{
		switch (state)
		{
		case 0:
			state = menu(window);
			break;
		case 1:
			state = credits(window);
			break;
		case 2:
			state = game(window);
			break;
		}
	}
	return 0;
}
