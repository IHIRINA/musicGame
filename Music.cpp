#include <windows.h>  
#include "Music.h"  
#include <mmsystem.h>  
#include <xmemory>  
#include <thread>  
#include <chrono>  
#pragma comment(lib, "winmm.lib")  

void Music::playBackgroundMusic(const char* filePath) {
    char command[100];
    sprintf_s(command, "open \"%s\" type mpegvideo alias bgMusic", filePath);
    mciSendStringA(command, NULL, 0, NULL);
    mciSendStringA("play bgMusic repeat", NULL, 0, NULL);
}

void Music::stopBackgroundMusic() {
    mciSendStringA("stop bgMusic", NULL, 0, NULL);
    mciSendStringA("close bgMusic", NULL, 0, NULL);
}