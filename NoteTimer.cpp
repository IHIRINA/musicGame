#include "NoteTimer.h"
#include <graphics.h>

void NoteTimer::init()
{
    if (isLoaded) return;

    timeIntervals.clear();
    intervalIndex = 0;
    lastNoteTime = clock();

    // 尝试读取文件
    std::ifstream file(filePath);
    if (file.is_open()) {
        int interval;
        while (file >> interval) {
            timeIntervals.push_back(interval);
        }
        file.close();
        printf("加载时间间隔文件成功，共 %zu 个间隔\n", timeIntervals.size());
    }
    else {
        printf("警告：无法打开 %s，使用默认时间间隔\n", filePath.c_str());
        loadDefaultIntervals();
    }
    isLoaded = true;
}

bool NoteTimer::generateNote(Assets& assets)
{
    if (intervalIndex >= timeIntervals.size()) {
        return false;  // 所有间隔已用完，不生成音符
    }

    clock_t currentTime = clock();
    if (currentTime - lastNoteTime >= timeIntervals[intervalIndex]) {
        // 生成新音符（随机X坐标，Y坐标固定为-40）
        int x = rand() % (getwidth() - 300) + 100;
        assets.addNote(x, -40);
        // 更新计时器和索引
        lastNoteTime = currentTime;
        intervalIndex++;
        return true;
    }
    return false;
}
