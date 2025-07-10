#pragma once
class Score
{
	int score = 0;  // ����
	int maxScore = 0;  // ��߷�
public:
	Score() = default;
	void addScore(int points) {
		score += points;
		if (score > maxScore) {
			maxScore = score;
		}
	}
	void resetScore() {
		score = 0;
	}
	int getScore() const {
		return score;
	}
	int getMaxScore() const {
		return maxScore;
	}
	void showScore(int width, int height);
};

