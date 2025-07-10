#include "Notes.h"
#include <cstdlib>
#include <time.h>
#include "Photos.h"

Notes::Notes(){}

Notes::Notes(int x, int y, int speed)
	:x(x),y(y),speed(speed),type(rand()%2)
{
}

void Notes::update() {
	if (isActive()) {
		y += speed;
	}
}

void Notes::render() {
	putimage(x, y, Photos::getInstance()->getImage(type == 0 ? "tab2" : "tab1"));
}