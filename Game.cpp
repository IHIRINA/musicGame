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
//��ʱʵ�ֺ���
void delayf(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
ExMessage Game::msg;
Notes note(0, 0, 5);
Assets assets;
Music music;

int Game::run() {
	//��Ϸ��ѭ��
	while (isRunning) {
		handleMsg();
		update();
		render();
		Sleep(5);
	}
	clean(); //������Դ
	return 0;
}

bool Game::init(int width, int height) {
	srand(time(NULL));
	initgraph(width, height, SHOWCONSOLE);
	music.playBackgroundMusic("./Resource/music/whipIt.wav");
	//�������е�ͼƬ
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
		NoteTimer("./Resource/time1.txt"),  // ��һ�׸��ʱ�����ļ�
		NoteTimer("./Resource/time2.txt"),  // �ڶ��׸��ʱ�����ļ�
		NoteTimer("./Resource/time3.txt")   // �����׸��ʱ�����ļ�
	};

	startTime = clock();
	isRunning = true;
	return true;
}

// ����Ⱦ���������ݵ�ǰҳ��״̬�л�
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

	// ʹ�õ�ǰѡ�е�NoteTimer
	noteTimers[selectedSongIndex].init();
	noteTimers[selectedSongIndex].generateNote(assets);

	// ��������״̬
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
		msg.message = 0;  // �����Ϣ�������ظ�����
	}


}


void Game::renderHomePage()
{
	BeginBatchDraw();

	// �ֲ�ͼ�߼�
	static int currentImage = 0;
	static int lastUpdateTime = clock();

	// ÿ1���л�һ��ͼƬ
	if (clock() - lastUpdateTime > 1000) {
		currentImage = (currentImage + 1) % 9;
		lastUpdateTime = clock();
	}

	// ���ز���ʾ��ǰͼƬ
	char fileName[100];
	IMAGE homeImage;  // ��ҳͼƬ����
	const char* basePath = "./Resource/images/home";
	sprintf_s(fileName, sizeof(fileName), "%s/%d.png", basePath, currentImage + 1);

	TCHAR tFileName[100];
#ifdef UNICODE
	mbstowcs_s(nullptr, tFileName, fileName, sizeof(tFileName) / sizeof(TCHAR));
#else
	strcpy_s(tFileName, fileName);
#endif

	loadimage(&homeImage, tFileName, 1400, 800, false);  // ����ͼƬ
	putimage(0, 0, &homeImage);  // ��ʾͼƬ 

	// ���Ʊ���
	settextcolor(BLACK);
	settextstyle(180, 90, _T("����"), 0, 0, 700, false, false, false);  // ����������ʽ
	setbkmode(TRANSPARENT);  // �������ֱ���͸��
	outtextxy(350, 150, _T("������Ϸ"));  // �ڻ�������ʾ����

	// ����"��ʼ"��ť
	settextcolor(BLACK);
	settextstyle(30, 0, "����");
	setlinecolor(WHITE);
	rectangle(getwidth() / 2 - 100, 450, getwidth() / 2 + 100, 500);  // ��ť�߿�
	outtextxy(getwidth() / 2 - 30, 460, "��ʼ");

	// ����"ESC����"��ʾ
	settextstyle(20, 0, "����");
	outtextxy(getwidth() - 150, getheight() - 50, "��ESC�˳���Ϸ");

	EndBatchDraw();
}

// ����Ŀ¼ҳ�������б�
void Game::renderSongListPage() {
	BeginBatchDraw();
	cleardevice();
	putimage(0, 0, Photos::getInstance()->getImage("content"));

	settextcolor(WHITE);
	settextstyle(60, 0, "����");
	outtextxy(150, 100, "ѡ�����");

	// ���Ƹ����б���ǰѡ���������
	settextstyle(30, 0, "����");
	for (int i = 0; i < Game::songList.size(); i++) {
		int yPos = 200 + i * 60;
		if (i == selectedSongIndex) {
			// ѡ���������
			setfillcolor(RGB(50, 100, 200));
			solidrectangle(200, yPos - 10, getwidth() - 200, yPos + 30);
		}
		settextcolor(WHITE);
		outtextxy(200, yPos, Game::songList[i].c_str());
	}
	EndBatchDraw();
}

// ������Ϸҳ��
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

	// ���Ʒ���
	settextcolor(BLACK);
	settextstyle(60, 0, _T("����"));

	char scoreText[20];
	sprintf_s(scoreText, sizeof(scoreText), "���յ÷�: %d", score.getScore());
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
		// ������¼�
		if (msg.message == WM_LBUTTONDOWN) {
			int x = msg.x;
			int y = msg.y;

			// ��ҳ�����"��ʼ"��ť����Ŀ¼ҳ
			if (currentPage == PageState::HOME) {
				// ��ť����(width/2-100, 400) �� (width/2+100, 450)
				int btnLeft = getwidth() / 2 - 100;
				int btnRight = getwidth() / 2 + 100;
				int btnTop = 450;
				int btnBottom = 500;
				if (x >= btnLeft && x <= btnRight && y >= btnTop && y <= btnBottom) {
					currentPage = PageState::SONG_LIST;
				}
			}

			// Ŀ¼ҳ���������������Ϸҳ
			else if (currentPage == PageState::SONG_LIST) {
				for (int i = 0; i < songList.size(); i++) {
					int yPos = 200 + i * 60;
					if (x >= 200 && x <= getwidth() - 200 && y >= yPos - 20 && y <= yPos + 20) {
						selectedSongIndex = i;
						std::string songPath = "./Resource/music/" + songListFolder[i];
						music.stopBackgroundMusic();
						music.playBackgroundMusic(songPath.c_str());
						currentPage = PageState::GAME;

						// ������Ϸ״̬
						startTime = clock();
						score.resetScore();
						assets.clean();

						// �ؼ��޸ģ��ӳٺ󲥷�����
						// �ӳٲ������֣������𲥷ţ�������ֹͣ��
						std::thread([this, songPath, selectedSongIndexCopy = selectedSongIndex]() {  // ����ѡ������
							std::vector<int> delays = { 1500, 0, 2500 };
							int delayTime = delays[selectedSongIndexCopy];  // ʹ�ø��Ƶ��������������߳��޸�Ӱ��
							std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));

							// ��������ǰ���ٴμ���Ƿ�������Ϸҳ����ֹ�û���;�˳���
							if (this->currentPage == PageState::GAME && this->selectedSongIndex == selectedSongIndexCopy) {
								music.stopBackgroundMusic();  // ֹ֮ͣǰ������
								music.playBackgroundMusic(songPath.c_str());  // ���ŵ�ǰ����
							}
							}).detach();
						break;
					}
				}
			}
		}

		// ���̰�����esc������һ��
		if (msg.message == WM_KEYDOWN) {
			if (msg.vkcode == VK_ESCAPE) {
				if (currentPage == PageState::SONG_LIST) {
					currentPage = PageState::HOME;  // Ŀ¼ҳ����ҳ
				}
				else if (currentPage == PageState::GAME) {
					Music::stopBackgroundMusic();
					currentPage = PageState::SONG_LIST;  // ��Ϸҳ��Ŀ¼ҳ
					noteTimers[selectedSongIndex].reset();
					assets.clean();
					music.playBackgroundMusic("./Resource/music/whipIt.wav");
				}
				else {
					quit();  // ��ҳ��ESC�˳�
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