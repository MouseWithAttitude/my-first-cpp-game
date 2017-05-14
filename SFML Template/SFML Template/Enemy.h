#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class Enemy {
public:
	Enemy(sf::Vector2f size) {
		enemy.setSize(size);
		enemy.setFillColor(sf::Color::Red);
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(enemy);
	}
	void move(sf::Vector2f distance) {
		enemy.move(distance);
	}

	sf::FloatRect getGlobalBounds() {
		return enemy.getGlobalBounds();
	}

	void setPos(sf::Vector2f newPos) {
		enemy.setPosition(newPos);
	}
	int getY() {
		return enemy.getPosition().y;
	}
	int getX() {
		return enemy.getPosition().x;
	}
	bool isCollidingWithCoin(Enemy *enemy2) {
		if (enemy.getGlobalBounds().intersects(enemy2->getGlobalBounds())) {
			return true;
		}
		return false;
	}

private:
	sf::RectangleShape enemy;
};