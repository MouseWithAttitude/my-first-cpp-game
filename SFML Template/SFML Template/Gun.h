#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class Gun {
public:
	Gun(sf::Vector2f size) {
		gun.setSize(size);
		gun.setFillColor(sf::Color::White);
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(gun);
	}
	void move(sf::Vector2f distance) {
		gun.move(distance);
	}

	sf::FloatRect getGlobalBounds() {
		return gun.getGlobalBounds();
	}

	void setPos(sf::Vector2f newPos) {
		gun.setPosition(newPos);
	}
	int getY() {
		return gun.getPosition().y;
	}
	int getX() {
		return gun.getPosition().x;
	}
	bool isCollidingWithCoin(Gun *gun2) {
		if (gun.getGlobalBounds().intersects(gun2->getGlobalBounds())) {
			return true;
		}
		return false;
	}

private:
	sf::RectangleShape gun;
};