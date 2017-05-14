#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Gun.h"
#include <sstream>
#include <cstdlib> 

using namespace sf;

int main() {
	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(1000, 1000), "SFML Game", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);
	

	//Player Object:

	float playerSize = 40;
	Player player({ playerSize,playerSize });
	player.setPos({ 50, 700 });

	//Coin Objects:
	std::vector<Coin*> coinVec;
	Coin coin1({ 20, 20 });
	Coin coin2({ 20, 20 });
	coinVec.push_back(&coin1);
	coinVec.push_back(&coin2);

	coin1.setPos({ 50, 600 });
	coin2.setPos({ 100, 600 });

	//Enemy Objects:
	Enemy enemyTemp({ 30, 30 });
	std::vector<Enemy*> enemyVec;
	std::vector<Enemy> enemys;

	for (int i = 0; i < 5; ++i) {
		enemys.push_back(enemyTemp);
	}
	
	for (int i = 0; i < enemys.size(); i++) {
		enemyVec.push_back(&enemys[i]);
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
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.move({ 0, moveSpeed });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move({ moveSpeed, 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move({ -moveSpeed, 0 });
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
				playerSize -= 5;
				player.setS({ playerSize,playerSize });
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
				playerSize += 10;
				player.setS({ playerSize,playerSize });
			}
		}


		//draw
		window.clear();
		coin1.drawTo(window);
		coin2.drawTo(window);
		for (int i = 0; i < enemyVec.size(); ++i) {
			enemys[i].drawTo(window);
		}
		player.drawTo(window);
		window.display();
	}
}