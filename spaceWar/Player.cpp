#include "Player.h"

void Player::initTexture()
{
	// Load a texture from file
	if (this->texture.loadFromFile("Texture/ship1.png") == false) {
		std::cout << "Not load texture file" << "\n";
	}
}

void Player::initSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//Resize
	this->sprite.scale(0.08f,0.08f);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

void Player::initVariables()
{
	this->movementSpeed = 15.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

Player::~Player()
{
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const sf::Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
	// TODO: insert return statement here
}

void Player::update()
{
	this->updateAttack();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}
