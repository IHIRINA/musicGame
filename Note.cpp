#include "Note.h"
#include <cstdlib>
#include <time.h>
#include "Photos.h"

Note::Note(){}

Note::Note(int x, int y, int speed)
	:x(x),y(y),speed(speed),type(rand()%2)
{
}

void Note::update() {
	if (isActive()) {
		y += speed;
	}
}

void Note::render() {
	putimage(x, y, Photos::getInstance()->getImage(type == 0 ? "tab2" : "tab1"));
}