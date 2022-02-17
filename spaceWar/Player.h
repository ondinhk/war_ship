#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	//private funtion
	void initTexture();
	void initSprite();
	void initVariables();

public:
	Player();
	virtual ~Player();
	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	//funtion
	void move(const float dirX, const float dirY);
	const bool canAttack();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

