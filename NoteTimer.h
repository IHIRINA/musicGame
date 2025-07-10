#pragma once
#include <vector>
#include <fstream>
#include <ctime>
#include "Assets.h"

class NoteTimer {
private:
    std::vector<int> timeIntervals;  // 存储时间间隔（毫秒）
    int intervalIndex = 0;           // 当前间隔索引
    clock_t lastNoteTime = 0;        // 上次生成音符的时间
    bool isLoaded = false;           // 是否已加载时间间隔
    std::string filePath;            // 时间间隔文件路径

    // 加载默认时间间隔（文件读取失败时使用）
    void loadDefaultIntervals() {
        timeIntervals = { 500, 800, 600, 700, 900 };  // 默认间隔示例
    }

public:
    // 构造函数：传入时间间隔文件路径
    NoteTimer(const std::string& path) : filePath(path) {}

    // 初始化：加载时间间隔文件（仅首次调用时执行）
    void init();

    // 根据时间间隔生成音符（返回是否生成了新音符）
    bool generateNote(Assets& assets);

    // 重置状态（切换歌曲或重新开始时调用）
    void reset() {
        isLoaded = false;  // 标记为未加载，下次init()时重新读取文件
        intervalIndex = 0;
        lastNoteTime = 0;
    }

    bool isAllNotesGenerated() const {
        return intervalIndex >= timeIntervals.size();
    }
};
