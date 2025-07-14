#pragma once
#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string password;
    std::vector<int> maxScores;
public:
    User(const std::string& u, const std::string& p) : username(u), password(p) {}

    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
        int getMaxScore(int songIndex) const {
        if (songIndex < maxScores.size()) {
            return maxScores[songIndex];
        }
        return 0;
    }
    void setMaxScore(int songIndex, int score) {
        if (songIndex >= maxScores.size()) {
            maxScores.resize(songIndex + 1, 0);
        }
        if (score > maxScores[songIndex]) {
            maxScores[songIndex] = score;
        }
    }
};