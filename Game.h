#pragma once
#include <graphics.h>
#include "Score.h"
#include <vector>
#include <string.h>
#include <string>
#include "NoteTimer.h"
#include <atomic>
#include <mutex>
#include "Animation.h"

// ҳ��״̬ö��
enum class PageState {
	LOGIN,      // ��¼ҳ��
	HOME,       // ��ҳ
	SONG_LIST,  // Ŀ¼ҳ�������б�
	GAME,       // ��Ϸҳ�棨���и���ҳ��
	SCORE,      //score
	PROFILE,
	HELP
};

class Game
{
	bool isRunning = false;
	int startTime = 0;
	int duration = 0;
	Score score;
	PageState currentPage = PageState::LOGIN;  // ��ǰҳ��״̬
	Animation animation;


	std::vector<std::string> songList = {     // �����б�����
		"1. ����",
		"2. ����ѭ��",
		"3. ��ô�ɰ����Ǳ�Ǹ",
		"4. ϲ���ͺ�ϲ���ķ���ʽ",

	};
	std::vector<std::string> songListFolder = {     // �����б�����
		"hana wumi.mp3",
		"koi.mp3",
		"kawaii.mp3",
		"suki.mp3",

	};

	std::vector<std::string> songBgImg = { 
		"bg4",
		"bg1",
		"bg2",
		"bg3",

	};
	int selectedSongIndex = 0;  // ��ǰѡ�еĸ�������

	std::vector<NoteTimer> noteTimers;  // ÿ��������Ӧһ��NoteTimer

	clock_t noteStartTime = 0;    // ��¼������ʼ�����ʱ��
	bool isNoteDropping = false;  // ��������Ƿ����ڵ���
	std::string username;         // �û���

public:
	static ExMessage msg;  //��Ϣ�ṹ
	std::string inputUsername;
	std::string inputPassword;
	int run();

	bool init(int width, int height);
	void clean();
	void update();
	void render();

	void quit() {
		isRunning = false;
	}

	void handleMsg();
	void handleEscapeKey();

	void renderHomePage();
	void renderSongListPage();
	void renderGamePage();
	void renderScorePage();
	void renderProfilePage();
	void renderLoginPage();
	void renderHelpPage();
};

