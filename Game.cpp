#include "Game.h"
#include <graphics.h>
#include <xmemory>  
#include <thread>  
#include <chrono>  
#include "Photos.h"
//��ʱʵ�ֺ���
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;

int Game::run() {
	
	//��Ϸ��ѭ��
	while (isRunning) {
		handleMsg(); 
		update();
		render();
	}
	clean(); //������Դ
	return 0;
}

bool Game::init(int width, int height) {
	initgraph(width, height, SHOWCONSOLE);

	//�������е�ͼƬ
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
	//����ͼƬ
	putimage(0, 0, Photos::getInstance()->getImage("bg1"));
}

void Game::handleMsg() {
	if (peekmessage(&msg)) {
		if (GetAsyncKeyState){
			if(msg.vkcode == VK_ESCAPE) { //�������ESC��
				quit();
			}
		}
	}
}