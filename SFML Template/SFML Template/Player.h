#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Coin.h"
#include "Enemy.h"

class Player {
public:
	Player(sf::Vector2f size) {
		player.setSize(size);
		player.setFillColor(sf::Color::Green);
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(player);
	}

	void move(sf::Vector2f distance) {
		player.move(distance);
	}

	void setS(sf::Vector2f size) {
		player.setSize(size);
	}

	void setPos(sf::Vector2f newPos) {
		player.setPosition(newPos);
	}

	int getY() {
		return player.getPosition().y;
	}
	int getX() {
		return player.getPosition().x;
	}

	bool isCollidingWithCoin(Coin *coin) {
		if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
			return true;
		}
		return false;
	}
	bool isCollidingWithEnemy(Enemy *enemy) {
		if (player.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
			return true;
		}
		return false;
	}
private:
	sf::RectangleShape player;
};