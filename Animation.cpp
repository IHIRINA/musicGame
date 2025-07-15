#include "Animation.h"
#include <iostream>

void Animation::addHitEffect(int x, int y)
{
    IMAGE* hitImg = Photos::getInstance()->getImage("click");
    if (hitImg == nullptr) {
        // ͼƬδ�ҵ������������Ϣ
        MessageBox(NULL, TEXT("hitͼƬδ�ҵ�"), TEXT("����"), MB_OK);
        return;
    }
    // ��ӵ�����Ϣ
    std::cout << "Adding hit effect at (" << x << ", " << y << ")" << std::endl;
    // ��ӵ�Ч���б�
    hitEffects.push_back({ x, y, clock(), hitImg });
}
void Animation::update()
{
    std::cout << "Updating hit effects..." << std::endl;
    clock_t currentTime = clock();
    // �Ƴ�������ʾʱ���Ч��
    for (auto it = hitEffects.begin(); it != hitEffects.end();) {
        if (currentTime - it->startTime > HIT_DURATION) {
            it = hitEffects.erase(it);  // �Ƴ�����Ч��
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
        // ʹ��Photos��͸����ͼ����
        Photos::getInstance()->putimage_alpha(
            effect.x, effect.y, effect.image
        );
    }
}

