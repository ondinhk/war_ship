#include "Game.h"
//Hàm chính để chạy game
void Game::initSystem()
{
	this->points = 0;
	this->isOverGame = false;
	this->startGame = false;
}

bool Game::isStart()
{
	return this->startGame;
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->updatePollEvents();
		if (isStart()) {
			if (!isOver()) {
				this->update();
			}
		}
		this->render();
	}
}

//Tạo khung màn hình 
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Space war", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	//this->window->setVerticalSyncEnabled(false);
}
//Tạo đối tượng viên đạn và hình ảnh viên đạn
void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
}
//Tạo biến kẻ thù
void Game::initEnemies()
{
	this->spawnTimeMax = 20.f;
	this->spawnTimer = this->spawnTimeMax;
}
//Tạo đối tượng phi thuyền
void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(this->window->getSize().x / 2 - this->player->getBounds().width
		, this->window->getSize().y);
}
//Khởi tạo giao diện số điểm
void Game::initGUI()
{
	//load font
	if (!this->font.loadFromFile("Fonts/times.ttf")) {
		std::cout << "Not load font";
	}
	//point
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(32);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Point");
	//Over Text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over !! Press Space to play again");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f
		, this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
	//Game start text
	this->gameStartText.setFont(this->font);
	this->gameStartText.setCharacterSize(60);
	this->gameStartText.setFillColor(sf::Color::Color(255, 230, 153));
	this->gameStartText.setString("Press Space to start game!!");
	this->gameStartText.setPosition(
		this->window->getSize().x / 2.f - this->gameStartText.getGlobalBounds().width / 2.f
		, this->window->getSize().y / 2.f - this->gameStartText.getGlobalBounds().height / 2.f);
}
//Khởi tạo background
void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Texture/background.jpg"))
		std::cout << "Not load background";
	this->worldBackground.setTexture(this->worldBackgroundTex);
	this->worldBackground.scale(1.f, 1.f);
}
bool Game::isOver()
{
	return this->isOverGame;
}
void Game::replayGame()
{
	delete this->player;
	this->clearEnemies();
	this->initSystem();
	this->initGUI();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
}
void Game::clearEnemies()
{
	this->bullets.clear();
	this->enemies.clear();
}
// Khởi tạo các đối tượng trong game
Game::Game()
{
	this->initWindow();
	this->initSystem();
	this->initGUI();
	this->initWorld();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
}

//Function
// Cập nhật phím đóng game
void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Space)
			this->startGame = true;
		if (isOver()) {
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Space)
			{
				this->replayGame();
			}
		}
	}
}

// Cập nhật phím di chuyển
void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 10.f, this->player->getPos().y, 0.f, -2.f, 10.f));
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 70.f, this->player->getPos().y, 0.f, -2.f, 10.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());
}

void Game::updateWorld()
{
}

// Ko cho player ra khỏi màn hình
void Game::updateCollision()
{
	// Left World, Right
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//Top,bottom
	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}


}

// Xóa viên đạn khi ra khoải màn hình top
void Game::updateBullet()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		//remove bullet at the top of the screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			//std::cout << this->bullets.size() << "\n";
		}
		++counter;
	}
}

// Tạo khối, và xóa khối khi khối xuống cuối màn hình, kiểm tra va chạm
void Game::updateEnemy()
{
	//Tạo khối cầu và vị trí khối cầu
	this->spawnTimer += 0.8f;
	if (this->spawnTimer >= this->spawnTimeMax) {
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}
	//Cập nhật vị trí khối cầu
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		int i = 0;
		enemy->update();
		//Xóa khối cầu khi xuống cuối màn hình
		if (enemy->getBounds().top > this->window->getSize().y) {
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
			//std::cout << this->enemies.size() << "\n";
		}
		else if (enemy->getBounds().intersects(this->player->getBounds())) {
			//Xóa khối cầu khi va chạm với tàu
			while (i <= 100) {
				i++;
			}
			this->isOverGame = true;
		}
		++counter;
	}
}

// Kiểm tra va chạm giữa đạn và khối cầu
void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t j = 0; j < this->bullets.size() && !enemy_deleted; j++) {
			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds())) {
				this->points += this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
				enemy_deleted = true;
			}
		}
	}
}
void Game::renderGUI()
{

	if (this->isOver()) {
		this->window->draw(this->gameOverText);
	}
	if (!this->isStart()) {
		this->window->draw(this->gameStartText);
	}
	else {
		this->window->draw(this->pointText);
	}
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}
void Game::update()
{
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateGUI();
	this->updateBullet();
	this->updateEnemy();
	this->updateCombat();
	this->updateWorld();
}

void Game::render()
{
	this->window->clear();
	this->renderWorld();
	this->player->render(*this->window);
	// Bullet
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	//Enemy
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	this->renderGUI();

	this->window->display();
}


