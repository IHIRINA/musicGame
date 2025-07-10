#pragma once
class Notes
{
	int x;
	int y;
	int speed;
	int type;
	bool active = true;
public:
	Notes();
	Notes(int x, int y, int speed = 3);
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


