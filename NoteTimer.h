#pragma once
#include <vector>
#include <fstream>
#include <ctime>
#include "Assets.h"

class NoteTimer {
private:
    std::vector<int> timeIntervals;  // �洢ʱ���������룩
    int intervalIndex = 0;           // ��ǰ�������
    clock_t lastNoteTime = 0;        // �ϴ�����������ʱ��
    bool isLoaded = false;           // �Ƿ��Ѽ���ʱ����
    std::string filePath;            // ʱ�����ļ�·��

    // ����Ĭ��ʱ�������ļ���ȡʧ��ʱʹ�ã�
    void loadDefaultIntervals() {
        timeIntervals = { 500, 800, 600, 700, 900 };  // Ĭ�ϼ��ʾ��
    }

public:
    // ���캯��������ʱ�����ļ�·��
    NoteTimer(const std::string& path) : filePath(path) {}

    // ��ʼ��������ʱ�����ļ������״ε���ʱִ�У�
    void init();

    // ����ʱ�������������������Ƿ���������������
    bool generateNote(Assets& assets);

    // ����״̬���л����������¿�ʼʱ���ã�
    void reset() {
        isLoaded = false;  // ���Ϊδ���أ��´�init()ʱ���¶�ȡ�ļ�
        intervalIndex = 0;
        lastNoteTime = 0;
    }

    bool isAllNotesGenerated() const {
        return intervalIndex >= timeIntervals.size();
    }
};
