#pragma once
#include <graphics.h>
class Game
{
	bool isRunning = false;
public:
	static ExMessage msg;  //消息结构
	int run();

	bool init(int width, int height);
	void clean();
	void update();
	void render();

	void quit() {
		isRunning = false;
	}

	void handleMsg();
};

