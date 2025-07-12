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
        int section = rand() % 4;
        int minX, maxX;
        switch (section) {
        case 0:
            minX = 0;
            maxX = 80;
            break;
        case 1:
            minX = 280;
            maxX = 360;
            break;
        case 2:
            minX = 560;
            maxX = 640;
            break;
        case 3:
            minX = 840;
            maxX = 920;
            break;
        }
        // 在选定的区间内随机生成X坐标，Y坐标固定为-40
        int x = rand() % (maxX - minX) + minX;
        assets.addNote(x, -40);
        // 更新计时信息
        lastNoteTime = currentTime;
        intervalIndex++;
        return true;
    }
    return false;
}
