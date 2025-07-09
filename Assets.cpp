#include "Assets.h"
#include <xmemory>
using namespace std;

void Assets::addNote(int x, int y, int speed)
{
	auto n = new Note(x,y,speed);
	notes.emplace_back(n);
}

void Assets::update() {
	for (auto& n : notes) {
		n->update();
	}
}

void Assets::render() {
	for (auto& n : notes) {
		n->render();
	}
}

void Assets::clean() {
	for (auto& n : notes) {
		
	}
}

void Assets::refresh()
{
	notes.erase(
		remove_if(notes.begin(), notes.end(), [](unique_ptr<Note>& n) {return n->isActive();}),
		notes.end());

}
