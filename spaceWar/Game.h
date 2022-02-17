#pragma once
#include"Player.h"
#include<map>
#include<string>
#include<sstream>
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	//window
	sf::RenderWindow* window;
	//Resources
	std::map<std::string, sf::Texture*> textures;
	//bullets
	std::vector<Bullet*> bullets;
	//Player
	Player* player;
	//Enemy
	float spawnTimer;
	float spawnTimeMax;
	std::vector<Enemy*> enemies;
	//Enemy* enemy;
	// GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;
	sf::Text gameStartText;
	//World
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;
	//Systems
	bool isOverGame;
	bool startGame;
	unsigned points;
	// init
	void initWindow();
	void initTextures();
	void initEnemies();
	void initPlayer();
	void initGUI();
	void initWorld();
	void initSystem();
	void replayGame();
	void clearEnemies();
	bool isOver();
	bool isStart();
public:
	Game();
	virtual ~Game();
	//funtion
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullet();
	void updateEnemy();
	void updateCombat();
	void update();
	void render();
	void renderGUI();
	void renderWorld();
};

