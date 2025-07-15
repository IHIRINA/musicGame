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
#include "UserManager.h"
#include <iostream>
#include <easyx.h>
#include "Animation.h"
using namespace std;
//延时实现函数
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;
Notes note(0, 0, 6);
Assets assets;
Music music;
Photos photos;
UserManager userManager;

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
	img->cacheImage("title", "./Resource/images/home/title.png", 850, 300);
	img->cacheImage("bg1", "./Resource/images/bg1.png", width, height);
	img->cacheImage("line", "./Resource/images/line.png", width);
	img->cacheImage("tab1", "./Resource/images/pink.png", 200, 50);
	img->cacheImage("tab2", "./Resource/images/blue.png", 200, 50);
	img->cacheImage("content", "./Resource/images/content.jpeg", width, height);
	img->cacheImage("bg2", "./Resource/images/bg2.png", width, height);
	img->cacheImage("bg3", "./Resource/images/bg3.png", width, height);
	img->cacheImage("score", "./Resource/images/score.jpg", width, height);
	img->cacheImage("bg4", "./Resource/images/bg4.jpg", width, height);
	img->cacheImage("login", "./Resource/images/profile.jpeg", width, height);
	img->cacheImage("start", "./Resource/images/start.png", 200, 50);
	img->cacheImage("button", "./Resource/images/home/button.png", 200, 50);
	
	img->cacheImage("click", "./Resource/images/click.png", 200, 200);

	noteTimers = {
		NoteTimer("./Resource/time1.txt"),  // 第一首歌的时间间隔文件
		NoteTimer("./Resource/time2.txt"),  // 第二首歌的时间间隔文件
		NoteTimer("./Resource/time3.txt"),   // 第三首歌的时间间隔文件
		NoteTimer("./Resource/time4.txt")   // 第四首歌的时间间隔文件
	};

	startTime = clock();
	isRunning = true;
	return true;
}

// 主渲染函数：根据当前页面状态切换
void Game::render() {
	switch (currentPage) {
	case PageState::LOGIN:
		renderLoginPage();
		break;
	case PageState::HOME:
		renderHomePage();
		break;
	case PageState::SONG_LIST:
		renderSongListPage();
		break;
	case PageState::GAME:
		renderGamePage();
		break;
	case PageState::SCORE:
		renderScorePage();
		break;
	case PageState::PROFILE:
		renderProfilePage();
		break;
	}
}

//清理资源函数
void Game::clean() {
	closegraph();
}

//更新
void Game::update() {
	if (currentPage != PageState::GAME) {
		return;
	}
	// 如果是第一次进入游戏页面，记录音符开始掉落时间
	if (!isNoteDropping) {
		noteStartTime = clock();
		isNoteDropping = true;
		noteTimers[selectedSongIndex].init();
		music.stopBackgroundMusic(); // 确保音乐还没开始
		return;
	}
	
	int delayTime[4] = { 675,900,350,300 };
	int speed[4] = { 2, 3, 4, 2 }; // 每首歌的音符速度

	if (clock() - noteStartTime >= delayTime[selectedSongIndex] && !music.isMusicPlaying()) {
		std::string songPath = "./Resource/music/" + songListFolder[selectedSongIndex];
		music.playBackgroundMusic(songPath.c_str());
	}

		// 使用当前选中的NoteTimer
		noteTimers[selectedSongIndex].init();
		noteTimers[selectedSongIndex].generateNote(assets,speed[selectedSongIndex]);

		// 更新音符状态
		assets.refresh();
		assets.update();

	}

//加载登录页面
void Game::renderLoginPage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage("login"));
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30, 0, "宋体");

	// 显示用户名输入提示
	outtextxy(500, 300, "用户名:");
	outtextxy(500, 350, inputUsername.c_str());

	// 显示密码输入提示
	outtextxy(500, 400, "密码:");
	std::string maskedPassword(inputPassword.length(), '*');
	outtextxy(500, 450, maskedPassword.c_str());

	// 显示登录按钮
	setlinecolor(WHITE);
	rectangle(600, 500, 800, 550);
	outtextxy(670, 510, "登录");

	EndBatchDraw();
	return;
}

//加载主页
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
	IMAGE* title = Photos::getInstance()->getImage("title");  // 获取标题图片
	Photos::getInstance()->putimage_alpha(300, 70, title);

	IMAGE* startButton = Photos::getInstance()->getImage("start");
	Photos::getInstance()->putimage_alpha(getwidth() / 2 - 100, 450, startButton);  // 绘制开始按钮
	
	IMAGE* profileButton = Photos::getInstance()->getImage("button");
	Photos::getInstance()->putimage_alpha(getwidth() / 2 - 100, 550, profileButton);  // 绘制个人中心按钮

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
	animation.update();  // 更新击中效果
	putimage(0, 0, Photos::getInstance()->getImage(songBgImg[selectedSongIndex]));
	putimage(0, 700, Photos::getInstance()->getImage("line"));
	animation.draw();  // 绘制所有击中效果
	setlinecolor(RED);
	line(280, 0, 280, 700);
	settextcolor(LIGHTGRAY);
	settextstyle(30, 40, _T("宋体"));
	outtextxy(100, 200, _T("S"));
	outtextxy(380, 200, _T("D"));
	outtextxy(660, 200, _T("F"));
	outtextxy(940, 200, _T("J"));
	outtextxy(1220, 200, _T("K"));
	line(560, 0, 560, 700);
	line(840, 0, 840, 700);
	line(1120, 0, 1120, 700);
	settextcolor(BLACK);
	settextstyle(30, 15, _T("宋体"));
	outtextxy(1100, 0, _T("按→结束游戏看得分"));
	assets.render();
	score.showScore(getwidth(), getheight());
	EndBatchDraw();
}

//绘制分数页面
void Game::renderScorePage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage("score"));

	// 绘制分数
	settextcolor(WHITE);
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

	// 保存最大分数
	
	if (userManager.getCurrentUser()) {
		userManager.getCurrentUser()->setMaxScore(selectedSongIndex, score.getScore());
	}

	settextstyle(30, 0, _T("宋体"));
	outtextxy(getwidth() / 2 - 100, getheight() - 100, _T("按ESC返回歌曲列表"));

	EndBatchDraw();
}

//绘制个人中心页面
void Game::renderProfilePage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage("login"));

	settextcolor(WHITE);
	settextstyle(60, 0, "宋体");
	outtextxy(150, 100, "个人中心");

	if (userManager.getCurrentUser()) {
		settextstyle(30, 0, "宋体");
		outtextxy(150, 200, ("用户名: " + userManager.getCurrentUser()->getUsername()).c_str());
        std::string scoreText1 = "1. 花海: " + std::to_string(userManager.getCurrentUser()->getMaxScore(0));  
        outtextxy(150, 250, scoreText1.c_str());
		std::string scoreText2 = "2. 恋爱循环: " + std::to_string(userManager.getCurrentUser()->getMaxScore(1));
		outtextxy(150, 300, scoreText2.c_str());
		std::string scoreText3 = "3. 这么可爱真是抱歉: " + std::to_string(userManager.getCurrentUser()->getMaxScore(2));
		outtextxy(150, 350, scoreText3.c_str());
		std::string scoreText4 = "4. 喜欢和好喜欢的方程式: " + std::to_string(userManager.getCurrentUser()->getMaxScore(3));
		outtextxy(150, 400, scoreText4.c_str());
	}

	settextstyle(30, 0, "宋体");
	outtextxy(getwidth() / 2 - 100, getheight() - 100, "按ESC返回首页");

	EndBatchDraw();
}

//处理鼠标键盘消息
void Game::handleMsg() {
	while (peekmessage(&msg)) {
		// 鼠标点击事件
		if (msg.message == WM_LBUTTONDOWN) {
			int x = msg.x;
			int y = msg.y;

			if (currentPage == PageState::LOGIN) {
				if (x >= 600 && x <= 800 && y >= 500 && y <= 550) {
                    if (!inputUsername.empty() && !inputPassword.empty()) {
						currentPage = PageState::HOME;
						userManager.addUser(inputUsername, inputPassword); // 添加新用户
						userManager.setCurrentUser(&userManager.users.back()); // 设置当前用户为新用户
					}
					else {
						// 登录失败提示
						MessageBox(NULL, TEXT("用户名或密码错误"), TEXT("登录失败"), MB_OK);
					}
				}
			}

			// 首页点击"开始"按钮进入目录页
			if (currentPage == PageState::HOME) {
				int btnLeft = getwidth() / 2 - 100;
				int btnRight = getwidth() / 2 + 100;
				int btnTop = 450;
				int btnBottom = 500;
				if (x >= btnLeft && x <= btnRight && y >= btnTop && y <= btnBottom) {
					currentPage = PageState::SONG_LIST;
				}
				// 首页点击"个人中心"按钮进入个人中心页
				btnTop = 550;
				btnBottom = 600;
				if (x >= btnLeft && x <= btnRight && y >= btnTop && y <= btnBottom) {
					currentPage = PageState::PROFILE;
				}
			}
			// 目录页：点击歌曲进入游戏页
			else if (currentPage == PageState::SONG_LIST) {
				for (int i = 0; i < songList.size(); i++) {
					int yPos = 200 + i * 60;
					if (x >= 200 && x <= getwidth() - 200 && y >= yPos - 20 && y <= yPos + 20) {
						selectedSongIndex = i;
						std::string songPath = "./Resource/music/" + songListFolder[i];
						music.stopBackgroundMusic(); // 停止当前音乐
						music.playBackgroundMusic(songPath.c_str()); // 播放选择歌曲
						currentPage = PageState::GAME;
						startTime = clock();
						score.resetScore();
						assets.clean();
						break;
					}
				}
			}
		}
		// 键盘按键事件
		else if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case VK_ESCAPE:
				handleEscapeKey();
				break;
			case VK_RETURN:
				if (currentPage == PageState::HOME) {
					currentPage = PageState::SONG_LIST;
				}
				else if (currentPage == PageState::LOGIN) {
					if (!inputUsername.empty() && !inputPassword.empty()) {
						currentPage = PageState::HOME;
						userManager.addUser(inputUsername, inputPassword); // 添加新用户
						userManager.setCurrentUser(&userManager.users.back()); // 设置当前用户为新用户
					}
					else {
						// 登录失败提示
						MessageBox(NULL, TEXT("用户名或密码错误"), TEXT("登录失败"), MB_OK);
					}
				}
				break;
			case VK_UP:
				if (currentPage == PageState::SONG_LIST && selectedSongIndex > 0) {
					selectedSongIndex--;
				}
				break;
			case VK_DOWN:
				if (currentPage == PageState::SONG_LIST && selectedSongIndex < songList.size() - 1) {
					selectedSongIndex++;
				}
				break;
			case VK_RIGHT:
				if (currentPage == PageState::GAME) {
					currentPage = PageState::SCORE;
					music.stopBackgroundMusic();
				}
				break;
			case VK_BACK:
				if (currentPage == PageState::LOGIN) {
					if (!inputPassword.empty()) {
						inputPassword.pop_back();
					}
					else if (!inputUsername.empty()) {
						inputUsername.pop_back();
					}
				}
				break;
			case 'S':
			case 'D':
			case 'F':
			case 'J':
			case 'K':
				if (currentPage == PageState::GAME) {
					const auto& notes = assets.note();
					bool hit = false;
					for (auto& n : notes) {
						int noteX = n->getX();
						int noteY = n->getY();
						int minX, maxX;
						switch (msg.vkcode) {
						case 'S':
							minX = 0;
							maxX = 280;
							break;
						case 'D':
							minX = 280;
							maxX = 560;
							break;
						case 'F':
							minX = 560;
							maxX = 840;
							break;
						case 'J':
							minX = 840;
							maxX = 1120;
							break;
						case 'K':
							minX = 1120;
							maxX = 1400;
							break;
						}
						if (noteY >= 670 && noteY <= 720 && noteX >= minX && noteX <= maxX) {
							n->destory();
							PlaySound(TEXT("./Resource/music/hitt.wav"), NULL, SND_FILENAME | SND_ASYNC);
							score.addScore(10);
							animation.addHitEffect(noteX, noteY-100);  // 添加击中效果
							score.addCombo();  // 增加连击数
							hit = true;
						}
					}
					if (!hit) {
						score.resetCombo();  // 未击中音符，重置连击数
					}
				}
				break;
			default:
				if (currentPage == PageState::LOGIN) {
					if (msg.ch >= ' ' && msg.ch <= '~') {
						if (inputUsername.length() < 20) {
							inputUsername += static_cast<char>(msg.ch);
						}
						else if (inputPassword.length() < 20) {
							inputPassword += static_cast<char>(msg.ch);
						}
					}
				}
				
				break;
			}
		}
	}
}

// 处理ESC键逻辑
void Game::handleEscapeKey() {
	switch (currentPage) {
	case PageState::SONG_LIST:
		currentPage = PageState::HOME;
		break;
	case PageState::GAME:
		music.stopBackgroundMusic();
		currentPage = PageState::SONG_LIST;
		noteTimers[selectedSongIndex].reset();
		assets.clean();
		music.playBackgroundMusic("./Resource/music/whipIt.wav");
		break;
	case PageState::SCORE:
		currentPage = PageState::SONG_LIST;
		music.playBackgroundMusic("./Resource/music/whipIt.wav");
		break;
	case PageState::PROFILE:
		currentPage = PageState::HOME;
		break;
	case PageState::LOGIN:
		currentPage = PageState::HOME;
		break;
	default:
		quit();
		break;
	}
}