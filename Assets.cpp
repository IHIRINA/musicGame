#include "Assets.h"
#include "Notes.h"

void Assets::addNote(int x, int y, int speed) {
    notes.push_back(std::make_shared<Notes>(x, y, speed));  // 使用 make_shared
}

void Assets::update() {
    for (auto& n : notes) {
        if (n) n->update();
    }
}

void Assets::render() {
    for (auto& n : notes) {
        if (n) n->render();
    }
}

void Assets::clean() {
    notes.clear();  // shared_ptr 会自动释放内存
}

void Assets::refresh() {
    // 使用 remove_if + erase 现在安全了，因为 shared_ptr 可以拷贝
    notes.erase(
        std::remove_if(notes.begin(), notes.end(),
            [](const std::shared_ptr<Notes>& n) {
                return !n->isActive();
            }),
        notes.end());
}