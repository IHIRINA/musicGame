#include "Game.h"
#include <graphics.h>
#include <xmemory>  
#include <thread>  
#include <chrono>  
#include "Photos.h"
#include "Music.h"
#include "Assets.h"
#include <vector>
#include "Notes.h"
using namespace std;
//延时实现函数
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;
Notes note(0, 0, 5);
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
	music.playBackgroundMusic("./Resource/music/whipIt.wav");
	//加载所有的图片
	auto img = Photos::getInstance();
	img->cacheImage("bg1", "./Resource/images/bg1.png", width, height);
	img->cacheImage("line", "./Resource/images/line.png", width);
	img->cacheImage("tab1", "./Resource/images/pink.png", 200, 50);
	img->cacheImage("tab2", "./Resource/images/blue.png", 200, 50);
	img->cacheImage("content", "./Resource/images/content.jpeg", width, height);
	img->cacheImage("bg2", "./Resource/images/bg2.png", width, height);
	img->cacheImage("bg3", "./Resource/images/bg3.png", width, height);
	img->cacheImage("score", "./Resource/images/score.jpg", width, height);

	noteTimers = {
		NoteTimer("./Resource/time1.txt"),  // 第一首歌的时间间隔文件
		NoteTimer("./Resource/time2.txt"),  // 第二首歌的时间间隔文件
		NoteTimer("./Resource/time3.txt")   // 第三首歌的时间间隔文件
	};

	startTime = clock();
	isRunning = true;
	return true;
}

// 主渲染函数：根据当前页面状态切换
void Game::render() {
	switch (currentPage) {
	case PageState::HOME:
		renderHomePage();
		break;
	case PageState::SONG_LIST:
		renderSongListPage();
		break;
	case PageState::GAME:
		renderGamePage();
		break;
	}
}

void Game::clean() {
	closegraph();
}

void Game::update() {
	if (currentPage != PageState::GAME) {
		return;
	}

	// 使用当前选中的NoteTimer
	noteTimers[selectedSongIndex].init();
	noteTimers[selectedSongIndex].generateNote(assets);

	// 更新音符状态
	assets.refresh();
	assets.update();

	if (msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE) {
		auto notes = assets.note();
		for (auto& n : notes) {
			if (n->getY() >= 670 && n->getY() <= 720) {
				n->destory();
				PlaySound(TEXT("./Resource/music/hit.mp3"), NULL, SND_FILENAME | SND_ASYNC);
				score.addScore(10);
			}
		}
		msg.message = 0;  // 清空消息，避免重复处理
	}


}


void Game::renderHomePage()
{
	BeginBatchDraw();

	// 轮播图逻辑
	static int currentImage = 0;
	static int lastUpdateTime = clock();

	// 每1秒切换一张图片
	if (clock() - lastUpdateTime > 1000) {
		currentImage = (currentImage + 1) % 9;
		lastUpdateTime = clock();
	}

	// 加载并显示当前图片
	char fileName[100];
	IMAGE homeImage;  // 首页图片对象
	const char* basePath = "./Resource/images/home";
	sprintf_s(fileName, sizeof(fileName), "%s/%d.png", basePath, currentImage + 1);

	TCHAR tFileName[100];
#ifdef UNICODE
	mbstowcs_s(nullptr, tFileName, fileName, sizeof(tFileName) / sizeof(TCHAR));
#else
	strcpy_s(tFileName, fileName);
#endif

	loadimage(&homeImage, tFileName, 1400, 800, false);  // 加载图片
	putimage(0, 0, &homeImage);  // 显示图片 

	// 绘制标题
	settextcolor(BLACK);
	settextstyle(180, 90, _T("宋体"), 0, 0, 700, false, false, false);  // 设置文字样式
	setbkmode(TRANSPARENT);  // 设置文字背景透明
	outtextxy(350, 150, _T("节奏游戏"));  // 在画布上显示文字

	// 绘制"开始"按钮
	settextcolor(BLACK);
	settextstyle(30, 0, "宋体");
	setlinecolor(WHITE);
	rectangle(getwidth() / 2 - 100, 450, getwidth() / 2 + 100, 500);  // 按钮边框
	outtextxy(getwidth() / 2 - 30, 460, "开始");

	// 绘制"ESC返回"提示
	settextstyle(20, 0, "宋体");
	outtextxy(getwidth() - 150, getheight() - 50, "按ESC退出游戏");

	EndBatchDraw();
}

// 绘制目录页（歌曲列表）
void Game::renderSongListPage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage("content"));

	settextcolor(WHITE);
	settextstyle(60, 0, "宋体");
	outtextxy(150, 100, "选择歌曲");

	// 绘制歌曲列表（当前选中项高亮）
	settextstyle(30, 0, "宋体");
	for (int i = 0; i < Game::songList.size(); i++) {
		int yPos = 200 + i * 60;
		if (i == selectedSongIndex) {
			// 选中项背景高亮
			setfillcolor(RGB(50, 100, 200));
			solidrectangle(200, yPos - 10, getwidth() - 200, yPos + 30);
		}
		settextcolor(WHITE);
		outtextxy(200, yPos, Game::songList[i].c_str());
	}
	EndBatchDraw();
}

// 绘制游戏页面
void Game::renderGamePage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage(songBgImg[selectedSongIndex]));
	putimage(0, 700, Photos::getInstance()->getImage("line"));
	assets.render();
	score.showScore(getwidth(), getheight());
	EndBatchDraw();
}

void Game::renderScorePage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage("score"));

	// 绘制分数
	settextcolor(BLACK);
	settextstyle(60, 0, _T("宋体"));

	char scoreText[20];
	sprintf_s(scoreText, sizeof(scoreText), "最终得分: %d", score.getScore());
	TCHAR tScoreText[20];
#ifdef UNICODE
	mbstowcs_s(nullptr, tScoreText, scoreText, sizeof(tScoreText) / sizeof(TCHAR));
#else
	strcpy_s(tScoreText, scoreText);
#endif

	int textWidth = textwidth(tScoreText);
	int x = (getwidth() - textWidth) / 2;
	int y = getheight() / 2 - 30;
	outtextxy(x, y, tScoreText);

	EndBatchDraw();
}

void Game::handleMsg() {
	if (peekmessage(&msg)) {
		// 鼠标点击事件
		if (msg.message == WM_LBUTTONDOWN) {
			int x = msg.x;
			int y = msg.y;

			// 首页：点击"开始"按钮进入目录页
			if (currentPage == PageState::HOME) {
				// 按钮区域：(width/2-100, 400) 到 (width/2+100, 450)
				int btnLeft = getwidth() / 2 - 100;
				int btnRight = getwidth() / 2 + 100;
				int btnTop = 450;
				int btnBottom = 500;
				if (x >= btnLeft && x <= btnRight && y >= btnTop && y <= btnBottom) {
					currentPage = PageState::SONG_LIST;
				}
			}

			// 目录页：点击歌曲进入游戏页
			else if (currentPage == PageState::SONG_LIST) {
				for (int i = 0; i < songList.size(); i++) {
					int yPos = 200 + i * 60;
					if (x >= 200 && x <= getwidth() - 200 && y >= yPos - 20 && y <= yPos + 20) {
						selectedSongIndex = i;
						std::string songPath = "./Resource/music/" + songListFolder[i];
						music.stopBackgroundMusic();
						music.playBackgroundMusic(songPath.c_str());
						currentPage = PageState::GAME;

						// 重置游戏状态
						startTime = clock();
						score.resetScore();
						assets.clean();

						// 关键修改：延迟后播放音乐
						// 延迟播放音乐（仅负责播放，不处理停止）
						std::thread([this, songPath, selectedSongIndexCopy = selectedSongIndex]() {  // 复制选中索引
							std::vector<int> delays = { 1500, 0, 2500 };
							int delayTime = delays[selectedSongIndexCopy];  // 使用复制的索引，避免主线程修改影响
							std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));

							// 播放音乐前，再次检查是否仍在游戏页（防止用户中途退出）
							if (this->currentPage == PageState::GAME && this->selectedSongIndex == selectedSongIndexCopy) {
								music.stopBackgroundMusic();  // 停止之前的音乐
								music.playBackgroundMusic(songPath.c_str());  // 播放当前歌曲
							}
							}).detach();
						break;
					}
				}
			}
		}

		// 键盘按键：esc返回上一级
		if (msg.message == WM_KEYDOWN) {
			if (msg.vkcode == VK_ESCAPE) {
				if (currentPage == PageState::SONG_LIST) {
					currentPage = PageState::HOME;  // 目录页→首页
				}
				else if (currentPage == PageState::GAME) {
					Music::stopBackgroundMusic();
					currentPage = PageState::SONG_LIST;  // 游戏页→目录页
					noteTimers[selectedSongIndex].reset();
					assets.clean();
					music.playBackgroundMusic("./Resource/music/whipIt.wav");
				}
				else {
					quit();  // 首页按ESC退出
				}
			}

			else if (msg.vkcode == VK_RETURN) {
				if (currentPage == PageState::HOME) {
					currentPage = PageState::SONG_LIST;
				}
			}

			if (msg.vkcode == VK_UP) {
				if (currentPage == PageState::SONG_LIST) {
					if (selectedSongIndex > 0) {
						selectedSongIndex--;
					}
				}
			}
			else if (msg.vkcode == VK_DOWN) {
				if (selectedSongIndex < songList.size() - 1) {
					selectedSongIndex++;
				}
			}

			if (msg.vkcode == VK_RIGHT) {
				if (currentPage == PageState::GAME) {
					currentPage = PageState::SCORE;
					music.stopBackgroundMusic();
				}
			}

		}
	}
}