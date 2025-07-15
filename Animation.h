#pragma once
#include <vector>
#include <easyx.h>
#include <ctime>
#include "Photos.h"  

class Animation {
private:
    // 单个击中效果的信息
    struct HitEffect {
        int x;          // 位置x
        int y;          // 位置y
        clock_t startTime;  // 开始显示的时间
        IMAGE* image;    // 击中效果图片
    };

    std::vector<HitEffect> hitEffects;  // 管理所有击中效果
    const int HIT_DURATION = 200;       // 击中效果显示时长（毫秒）

public:
    void addHitEffect(int x, int y);

    // 更新所有击中效果（移除过期的效果）
    void update();

    // 绘制所有有效的击中效果
    void draw();
};
