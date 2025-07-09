#include "Game.h"
#include <graphics.h>
#include <xmemory>  
#include <thread>  
#include <chrono>  
#include "Photos.h"
#include "Music.h"
#include "Assets.h"
#include <vector>
using namespace std;
//延时实现函数
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;
Note note(0,0,5);
Assets assets;
Music music;

int Game::run() {
	//游戏主循环
	while (isRunning) {
		handleMsg(); 
		update();
		render();
		Sleep(5);
	}
	clean(); //清理资源
	return 0;
}

bool Game::init(int width, int height) {
	srand(time(NULL));
	initgraph(width, height, SHOWCONSOLE);
	music.playBackgroundMusic("./Resource/music/koi.mp3");
	//加载所有的图片
	auto img = Photos::getInstance();
	img->cacheImage("bg1", "./Resource/images/bg1.png",width,height);
	img->cacheImage("line", "./Resource/images/line.png", width);
	img->cacheImage("tab1", "./Resource/images/pink.png",200,50);
	img->cacheImage("tab2", "./Resource/images/blue.png",200,50);

	startTime = clock();

	isRunning = true;  
	return true;
}

void Game::clean() {
	closegraph();
}

void Game::update() {
	duration = (clock() - startTime)/1000;
	assets.refresh();
	assets.update();

	static int t1 = 0;

	//游戏运行1秒以后添加note
	if (duration > 1) {
		if ((clock() - t1) > 600) {
			assets.addNote(rand() % (getwidth()-300)+100, -40);
			t1 = clock();
		}
	}

	//检测键盘按下时是否刚好在判定线上
	auto notes = assets.note();
	for (auto& n : notes) {
		if (n->getY() >= 700 - 20 && n->getY() >= 700 + 30) {
			n->destory();
			music.playBackgroundMusic("./Resource/music/");
		}
	}

}

void Game::render() {
	BeginBatchDraw(); //开始批量绘图
	cleardevice();
	//绘制图片
	putimage(0, 0, Photos::getInstance()->getImage("bg1"));
	putimage(0, 700, Photos::getInstance()->getImage("line"));
	assets.render();
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