#pragma once
class Score
{
    int score = 0;  // 分数
    int maxScore = 0;  // 最高分
    int combo = 0;  // 连击数

public:
    Score() = default;
    void addScore(int points);
    void addCombo();  // 增加连击数
    void resetCombo();  // 重置连击数
    int getCombo() const;  // 获取连击数
    void resetScore();
    int getScore() const {
		return score;
    }
    int getMaxScore() const {
		return maxScore;
    }
    void showScore(int width, int height);
};
