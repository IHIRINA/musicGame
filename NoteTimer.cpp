#include "NoteTimer.h"
#include <graphics.h>

void NoteTimer::init()
{
    if (isLoaded) return;

    timeIntervals.clear();
    intervalIndex = 0;
    lastNoteTime = clock();

    // ���Զ�ȡ�ļ�
    std::ifstream file(filePath);
    if (file.is_open()) {
        int interval;
        while (file >> interval) {
            timeIntervals.push_back(interval);
        }
        file.close();
        printf("����ʱ�����ļ��ɹ����� %zu �����\n", timeIntervals.size());
    }
    else {
        printf("���棺�޷��� %s��ʹ��Ĭ��ʱ����\n", filePath.c_str());
        loadDefaultIntervals();
    }
    isLoaded = true;
}

bool NoteTimer::generateNote(Assets& assets)
{
    if (intervalIndex >= timeIntervals.size()) {
        return false;  // ���м�������꣬����������
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
        // ��ѡ�����������������X���꣬Y����̶�Ϊ-40
        int x = rand() % (maxX - minX) + minX;
        assets.addNote(x, -40);
        // ���¼�ʱ��Ϣ
        lastNoteTime = currentTime;
        intervalIndex++;
        return true;
    }
    return false;
}
