#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cstdlib> 
#include <fstream>
#include <cctype>
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Gun.h"


using namespace sf;

int main() {
	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(1000, 1000), "SFML Game", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);
	
	//Variables
	enum enumDirection{left,up,right,down};
	int direction = left;

	//Score Objects:

	int score = 0;

	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	std::ostringstream ssScore;
	ssScore << "Score: " << score;

	sf::Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition({ 10, 10 });
	lblScore.setFont(arial);
	lblScore.setString(ssScore.str());

	//Player Object:

	float playerSize = 40;
	Player player({ playerSize,playerSize });
	player.setPos({ 50, 700 });
	Gun gun({ playerSize / 75,playerSize / 90 });
	//gun.setPos({ , });


	//coin Objects:
	Coin coinTemp({ 20, 20 });
	std::vector<Coin*> coinVec;
	std::vector<Coin> coins;
	std::vector<bool> coinVisable;

	for (int i = 0; i < 5; ++i) {
		coins.push_back(coinTemp);
	}

	for (int i = 0; i < coins.size(); i++) {
		coinVec.push_back(&coins[i]);
		coinVisable.push_back(true);
		coinVec[i]->setPos({ (float)(100 * i), 50 });
	}


	//Enemy Objects:
	Enemy enemyTemp({ 30, 30 });
	std::vector<Enemy*> enemyVec;
	std::vector<Enemy> enemys;
	std::vector<bool> enemyVisable;

	for (int i = 0; i < 5; ++i) {
		enemys.push_back(enemyTemp);
	}
	
	for (int i = 0; i < enemys.size(); i++) {
		enemyVec.push_back(&enemys[i]);
		enemyVisable.push_back(true);
		enemyVec[i]->setPos({ (float)(100*i), 50 });
	}




	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		const float moveSpeed = 0.2;
		const float enemyMoveSpeed = 0.05;

		//player movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.move({ 0, -moveSpeed });
			direction = up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.move({ 0, moveSpeed });
			direction = down;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move({ moveSpeed, 0 });
			direction = right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move({ -moveSpeed, 0 });
			direction = left;
		}
		
		
		//enemy logic
		for (int i = 0; i < enemyVec.size(); ++i) {
			if (player.getX() > enemys[i].getX()) {
				enemys[i].move({ enemyMoveSpeed, 0 });
			}
			if (player.getX() < enemys[i].getX()) {
				enemys[i].move({ -enemyMoveSpeed, 0 });
			}
			if (player.getY() > enemys[i].getY()) {
				enemys[i].move({ 0,enemyMoveSpeed });
			}
			if (player.getY() < enemys[i].getY()) {
				enemys[i].move({ 0,-enemyMoveSpeed});
			}
		}
		for (int i = 0; i < enemyVec.size(); i++) {
			if (player.isCollidingWithEnemy(enemyVec[i])) {
				enemyVec[i]->setPos({ (float)(rand() % 1000) , (float)(rand() % 1000) });
			}
		}
		for (int i = 0; i < enemyVec.size(); i++) {
		}

		

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			}
		}



		//Coin Logic:
		for (int i = 0; i < coinVec.size(); i++) {
			if (player.isCollidingWithCoin(coinVec[i])) {
				coinVec[i]->setPos({ (float)(rand() % 1000), (float)(rand() % 1000) });
				//coinVisable[i] = false;
				score++;
				ssScore.str("");
				ssScore << "Score " << score;
				lblScore.setString(ssScore.str());
			}
		}


		//draw
		window.clear();
		for (int i = 0; i < coinVec.size(); ++i) {
			coins[i].drawTo(window, coinVisable[i]);
		}
		for (int i = 0; i < enemyVec.size(); ++i) {
			enemys[i].drawTo(window, enemyVisable[i]);
		}
		player.drawTo(window);
		window.draw(lblScore);
		window.display();
	}
}