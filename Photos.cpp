#include "Photos.h"  
#include "easyx.h" 
#include <iostream>
using namespace std;

Photos* Photos::getInstance()
{
    static Photos p;

    return &p;
}

IMAGE* Photos::loadImage(const string& file, int width, int height) {
    IMAGE* img = new IMAGE;
    ::loadimage(img, file.data(), width, height);
    if (img->getheight() == 0 || img->getwidth() == 0) {
        cout << "load image< " << file << ">failed" << endl;
        delete img;
        return nullptr;
    }
    return img;
}

void Photos::cacheImage(const string& tag, const string& file, int width, int height) {
    auto it = images.find(tag);
    if (it == images.end()) {
        cout << "tag is<" << tag << ">image is exists" << endl;
        return;
    }

    IMAGE* img = loadImage(file, width, height);   //ох╪сть
    //cache
    if (img) {
        auto it = images.emplace(tag, img);
    }
}

IMAGE* Photos::getImage(const string& tag) {
    auto it = images.find(tag);
    if (it == images.end()) {
        cout << "not find tag is<" << tag << ">image" << endl;
        return nullptr;
    }
    return it->second.get();
}