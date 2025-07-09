#include "Game.h"
#include <graphics.h>
#include <xmemory>  
#include <thread>  
#include <chrono>  
#include "Photos.h"
//延时实现函数
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;

int Game::run() {
	
	//游戏主循环
	while (isRunning) {
		handleMsg(); 
		update();
		render();
	}
	clean(); //清理资源
	return 0;
}

bool Game::init(int width, int height) {
	initgraph(width, height, SHOWCONSOLE);

	//加载所有的图片
	auto img = Photos::getInstance();
	img->cacheImage("bg1", "./Resource/images/bg1.png");

	isRunning = true;
	return true;
}

void Game::clean() {
	closegraph();
}

void Game::update() {
	
}

void Game::render() {
	//绘制图片
	putimage(0, 0, Photos::getInstance()->getImage("bg1"));
}

void Game::handleMsg() {
	if (peekmessage(&msg)) {
		if (GetAsyncKeyState){
			if(msg.vkcode == VK_ESCAPE) { //如果按下ESC键
				quit();
			}
		}
	}
}