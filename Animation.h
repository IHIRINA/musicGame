#pragma once
#include <vector>
#include <easyx.h>
#include <ctime>
#include "Photos.h"  

class Animation {
private:
    // ��������Ч������Ϣ
    struct HitEffect {
        int x;          // λ��x
        int y;          // λ��y
        clock_t startTime;  // ��ʼ��ʾ��ʱ��
        IMAGE* image;    // ����Ч��ͼƬ
    };

    std::vector<HitEffect> hitEffects;  // �������л���Ч��
    const int HIT_DURATION = 200;       // ����Ч����ʾʱ�������룩

public:
    void addHitEffect(int x, int y);

    // �������л���Ч�����Ƴ����ڵ�Ч����
    void update();

    // ����������Ч�Ļ���Ч��
    void draw();
};
