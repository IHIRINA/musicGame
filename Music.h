#pragma once
class Music
{
public:
	static void playBackgroundMusic(const char* filePath);
	static void stopBackgroundMusic();
	bool isMusicPlaying() const;
	bool isMusicFinished();
};

