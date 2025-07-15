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

// 页面状态枚举
enum class PageState {
	LOGIN,      // 登录页面
	HOME,       // 首页
	SONG_LIST,  // 目录页（歌曲列表）
	GAME,       // 游戏页面（现有歌曲页）
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
	PageState currentPage = PageState::LOGIN;  // 当前页面状态
	Animation animation;


	std::vector<std::string> songList = {     // 歌曲列表数据
		"1. 花海",
		"2. 恋爱循环",
		"3. 这么可爱真是抱歉",
		"4. 喜欢和好喜欢的方程式",

	};
	std::vector<std::string> songListFolder = {     // 歌曲列表数据
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
	int selectedSongIndex = 0;  // 当前选中的歌曲索引

	std::vector<NoteTimer> noteTimers;  // 每个歌曲对应一个NoteTimer

	clock_t noteStartTime = 0;    // 记录音符开始掉落的时间
	bool isNoteDropping = false;  // 标记音符是否正在掉落
	std::string username;         // 用户名

public:
	static ExMessage msg;  //消息结构
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

