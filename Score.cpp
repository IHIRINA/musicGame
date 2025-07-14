#include "Score.h"
#include <stdio.h>
#include <easyx.h>

void Score::addScore(int points) {
    // 根据连击数调整得分
    int comboBonus = combo / 5 + 1;  // 每 5 连击增加 1 倍得分
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
    combo = 0;  // 重置分数时同时重置连击数
}

void Score::showScore(int width, int height)
{
    // 显示分数
    char scoreText[20];
    sprintf_s(scoreText, "Score: %d", getScore());
    settextcolor(BLACK);
    settextstyle(30, 0, _T("宋体"));
    setbkmode(TRANSPARENT);
    int textWidth = textwidth(scoreText);
    int textHeight = textheight(scoreText);
    int x = (getwidth() - textWidth) / 2;
    int y = 5;
    outtextxy(x, y, scoreText);

    // 显示连击数
    char comboText[20];
    sprintf_s(comboText, "Combo: %d", getCombo());
    int comboTextWidth = textwidth(comboText);
    int comboTextHeight = textheight(comboText);
    int comboX = (getwidth() - comboTextWidth) / 2;
    int comboY = y + textHeight + 5;
    outtextxy(comboX, comboY, comboText);
}