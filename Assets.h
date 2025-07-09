#pragma once
#include <vector>
#include <memory>
#include "Note.h"
using namespace std;
class Assets
{
	vector<unique_ptr<Note>> notes;
public:
	void addNote(int x, int y, int speed = 3);
	void update();
	void render();
	void clean();
	void refresh();
	vector<unique_ptr<Note>>& note() {
		return notes;
	}
};

