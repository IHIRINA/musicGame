#include<iostream>
#include <graphics.h>
#include "Game.h"

using namespace std;

int main() {
	Game game;
	game.init(1400, 800);

	cout << "只有输入了用户名和密码才可以进入游戏哦" << endl;
	cout << "请输入用户名: " << endl;
	cin >> game.inputUsername;  // 从控制台输入用户名
	cout << "请输入密码: " << endl;
	cin >> game.inputPassword;  // 从控制台输入密码

	return game.run();
}