#include"Game.h"
#include<time.h>
int main() {
	std::srand(static_cast<unsigned>(time(0)));
	Game game;
	game.run();
	return 0;
}