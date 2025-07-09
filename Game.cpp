#include "Game.h"
#include <graphics.h>
#include <xmemory>  
#include <thread>  
#include <chrono>  
#include "Photos.h"
#include "Music.h"
#include "Note.h"
//��ʱʵ�ֺ���
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;
Note note;

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
	Music music;
	music.playBackgroundMusic("./Resource/music/koi.mp3");
	//�������е�ͼƬ
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
	BeginBatchDraw(); //��ʼ������ͼ
	cleardevice();
	//����ͼƬ
	putimage(0, 0, Photos::getInstance()->getImage("bg1"));
	putimage(0, 700, Photos::getInstance()->getImage("line"));
	note.render();
	EndBatchDraw();
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