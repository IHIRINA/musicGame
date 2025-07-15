#pragma once  
#include "easyx.h"
#include <map>  
#include <string>  
#include <memory>
#include <windows.h>
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "Winmm.LIB")
using namespace std;  

class Photos  
{  
private:   
	map<string, unique_ptr<IMAGE>> images;  
public:  
	static Photos* getInstance();
	IMAGE* loadImage(const string& file, int width = 0, int height = 0);  
	void cacheImage(const string& tag, const string& file, int width = 0, int height = 0);
	IMAGE* getImage(const string& tag);

	// ÏÔÊ¾Í¸Ã÷Í¼Æ¬
	void putimage_alpha(int x, int y, IMAGE* img)
	{
		int w = img->getwidth();
		int h = img->getheight();
		AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
	}
};
