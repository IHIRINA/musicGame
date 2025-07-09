#include "Game.h"
#include <graphics.h>
#include <xmemory>  
#include <thread>  
#include <chrono>  
#include "Photos.h"
#include "Music.h"
#include "Note.h"
//延时实现函数
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;
Note note;

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
	Music music;
	music.playBackgroundMusic("./Resource/music/koi.mp3");
	//加载所有的图片
	auto img = Photos::getInstance();
	img->cacheImage("bg1", "./Resource/images/bg1.png",width,height);
	img->cacheImage("line", "./Resource/images/line.png", width);
	img->cacheImage("tab1", "./Resource/images/pink.png",200,50);
	img->cacheImage("tab2", "./Resource/images/blue.png");

	isRunning = true;  
	return true;
}

void Game::clean() {
	closegraph();
}

void Game::update() {
	note.update();
}

void Game::render() {
	BeginBatchDraw(); //开始批量绘图
	cleardevice();
	//绘制图片
	putimage(0, 0, Photos::getInstance()->getImage("bg1"));
	putimage(0, 700, Photos::getInstance()->getImage("line"));
	note.render();
	EndBatchDraw();
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