#include "Animation.h"
#include <iostream>

void Animation::addHitEffect(int x, int y)
{
    IMAGE* hitImg = Photos::getInstance()->getImage("click");
    if (hitImg == nullptr) {
        // 图片未找到，输出错误信息
        MessageBox(NULL, TEXT("hit图片未找到"), TEXT("错误"), MB_OK);
        return;
    }
    // 添加调试信息
    std::cout << "Adding hit effect at (" << x << ", " << y << ")" << std::endl;
    // 添加到效果列表
    hitEffects.push_back({ x, y, clock(), hitImg });
}
void Animation::update()
{
    std::cout << "Updating hit effects..." << std::endl;
    clock_t currentTime = clock();
    // 移除超过显示时间的效果
    for (auto it = hitEffects.begin(); it != hitEffects.end();) {
        if (currentTime - it->startTime > HIT_DURATION) {
            it = hitEffects.erase(it);  // 移除过期效果
        }
        else {
            ++it;
        }
    }
}

void Animation::draw()
{
    std::cout << "Drawing hit effects..." << std::endl;
    for (const auto& effect : hitEffects) {
        // 使用Photos的透明绘图方法
        Photos::getInstance()->putimage_alpha(
            effect.x, effect.y, effect.image
        );
    }
}

