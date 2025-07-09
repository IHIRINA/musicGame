#pragma once  
#include "easyx.h"
#include <map>  
#include <string>  
#include <memory>
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

};
