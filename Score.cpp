#include "Score.h"
#include <stdio.h>
#include <easyx.h>

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
}
