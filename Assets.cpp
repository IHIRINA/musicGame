#include "Assets.h"
#include "Notes.h"

void Assets::addNote(int x, int y, int speed) {
    notes.push_back(std::make_shared<Notes>(x, y, speed));  // ʹ�� make_shared
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
    notes.clear();  // shared_ptr ���Զ��ͷ��ڴ�
}

void Assets::refresh() {
    // ʹ�� remove_if + erase ���ڰ�ȫ�ˣ���Ϊ shared_ptr ���Կ���
    notes.erase(
        std::remove_if(notes.begin(), notes.end(),
            [](const std::shared_ptr<Notes>& n) {
                return !n->isActive();
            }),
        notes.end());
}