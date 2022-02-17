#include "Enemy.h"

//Tạo khối cầu
void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->speed = static_cast<float>(this->pointCount*2);
	this->points = this->pointCount;
}
void Enemy::initShape()
{
	//Set kích thước
	this->shape.setRadius(rand() % 20 + 35);
	// Set số cạnh
	this->shape.setPointCount(this->pointCount);
	// Màu
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
Enemy::Enemy()
{
}

Enemy::Enemy(float pos_x,float pos_y)
{ 
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}
const int& Enemy::getPoints() const
{
	// TODO: insert return statement here
	return this->points;
}
// Funtions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
