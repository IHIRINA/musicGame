#pragma once
class Score
{
    int score = 0;  // ����
    int maxScore = 0;  // ��߷�
    int combo = 0;  // ������

public:
    Score() = default;
    void addScore(int points);
    void addCombo();  // ����������
    void resetCombo();  // ����������
    int getCombo() const;  // ��ȡ������
    void resetScore();
    int getScore() const {
		return score;
    }
    int getMaxScore() const {
		return maxScore;
    }
    void showScore(int width, int height);
};
