#pragma once
#include <vector>
#include <memory>
#include "Notes.h"

class Assets {
    std::vector<std::shared_ptr<Notes>> notes;  // ���� shared_ptr

public:
    void addNote(int x, int y, int speed = 5);
    void update();
    void render();
    void clean();
    void refresh();

    // ���س�������
    const std::vector<std::shared_ptr<Notes>>& note() const {
        return notes;
    }
};
