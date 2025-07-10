#pragma once
#include <graphics.h>
#include "Score.h"
#include <vector>
#include <string.h>
#include <string>
#include "NoteTimer.h"

// 页面状态枚举
enum class PageState {
	HOME,       // 首页
	SONG_LIST,  // 目录页（歌曲列表）
	GAME,       // 游戏页面（现有歌曲页）
	SCORE       //score
};

class Game
{
	bool isRunning = false;
	int startTime = 0;
	int duration = 0;
	Score score;
	PageState currentPage = PageState::HOME;  // 当前页面状态
	std::vector<std::string> songList = {     // 歌曲列表数据
		"1. 恋爱循环",
		"2. 这么可爱真是抱歉",
		"3. 喜欢和好喜欢的方程式"
	};
	std::vector<std::string> songListFolder = {     // 歌曲列表数据
		"koi.mp3",
		"kawaii.mp3",
		"suki.mp3"
	};

	std::vector<std::string> songBgImg = {   
		"bg1",
		"bg2",
		"bg3"
	};
	int selectedSongIndex = 0;  // 当前选中的歌曲索引

	std::vector<NoteTimer> noteTimers;  // 每个歌曲对应一个NoteTimer

public:
	static ExMessage msg;  //消息结构
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

