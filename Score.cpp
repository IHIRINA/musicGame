#include "Score.h"
#include <stdio.h>
#include <easyx.h>

void Score::addScore(int points) {
    // ���������������÷�
    int comboBonus = combo / 5 + 1;  // ÿ 5 �������� 1 ���÷�
    score += points * comboBonus;
    if (score > maxScore) {
        maxScore = score;
    }
}

void Score::addCombo() {
    combo++;
}

void Score::resetCombo() {
    combo = 0;
}

int Score::getCombo() const {
    return combo;
}

void Score::resetScore() {
    score = 0;
    combo = 0;  // ���÷���ʱͬʱ����������
}

void Score::showScore(int width, int height)
{
    // ��ʾ����
    char scoreText[20];
    sprintf_s(scoreText, "Score: %d", getScore());
    settextcolor(BLACK);
    settextstyle(30, 0, _T("����"));
    setbkmode(TRANSPARENT);
    int textWidth = textwidth(scoreText);
    int textHeight = textheight(scoreText);
    int x = (getwidth() - textWidth) / 2;
    int y = 5;
    outtextxy(x, y, scoreText);

    // ��ʾ������
    char comboText[20];
    sprintf_s(comboText, "Combo: %d", getCombo());
    int comboTextWidth = textwidth(comboText);
    int comboTextHeight = textheight(comboText);
    int comboX = (getwidth() - comboTextWidth) / 2;
    int comboY = y + textHeight + 5;
    outtextxy(comboX, comboY, comboText);
}