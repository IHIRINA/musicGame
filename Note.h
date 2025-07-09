#pragma once
class Note
{
	int x;
	int y;
	int speed;
	int type;
	bool active = true;
public:
	Note();
	Note(int x, int y, int speed = 3);
	void update();
	void render();
	void destory() {
		active = false;
	}
	bool isActive() const{
		return active;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};


