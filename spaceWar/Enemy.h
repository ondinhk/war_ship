#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include<SFML/Graphics.hpp>
class Enemy
{
private:
	sf::CircleShape shape;
	unsigned pointCount;
	float speed;
	int points;

	void initShape();
	void initVariables();

public:
	Enemy();
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	//accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	//funtion

	void update();
	void render(sf::RenderTarget* target);
};
#endif // !ENEMY_H

