#include<iostream>
#include <graphics.h>
#include "Game.h"
using namespace std;

int main() {
	Game game;
	game.init(1400, 800);
	return game.run();
}