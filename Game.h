#pragma once
#include <graphics.h>
#include "Score.h"
#include <vector>
#include <string.h>
#include <string>
#include "NoteTimer.h"

// ҳ��״̬ö��
enum class PageState {
	HOME,       // ��ҳ
	SONG_LIST,  // Ŀ¼ҳ�������б�
	GAME,       // ��Ϸҳ�棨���и���ҳ��
	SCORE       //score
};

class Game
{
	bool isRunning = false;
	int startTime = 0;
	int duration = 0;
	Score score;
	PageState currentPage = PageState::HOME;  // ��ǰҳ��״̬
	std::vector<std::string> songList = {     // �����б�����
		"1. ����ѭ��",
		"2. ��ô�ɰ����Ǳ�Ǹ",
		"3. ϲ���ͺ�ϲ���ķ���ʽ"
	};
	std::vector<std::string> songListFolder = {     // �����б�����
		"koi.mp3",
		"kawaii.mp3",
		"suki.mp3"
	};

	std::vector<std::string> songBgImg = {   
		"bg1",
		"bg2",
		"bg3"
	};
	int selectedSongIndex = 0;  // ��ǰѡ�еĸ�������

	std::vector<NoteTimer> noteTimers;  // ÿ��������Ӧһ��NoteTimer

public:
	static ExMessage msg;  //��Ϣ�ṹ
	int run();

	bool init(int width, int height);
	void clean();
	void update();
	void render();

	void quit() {
		isRunning = false;
	}

	void handleMsg();

	void renderHomePage();
	void renderSongListPage();
	void renderGamePage();
	void renderScorePage();
};

