#pragma once
#ifndef BULLET_H
#define BULLET_H
#endif // !BULLET_H
#include<SFML/Graphics.hpp>
#include<iostream>
class Bullet
{
private:
	sf::Sprite shape;
	sf::Texture* texture;
	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x,float pos_y,float dirX, float dirY, float movementSpeed);
	virtual  ~Bullet();

	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};

