#include "SoundSE.h"



SoundSE::SoundSE()
{

	bgm[0] = Sound(L"AAA/nosound.wav");
	bgm[1] = Sound(L"AAA/BGM01.wav");
	bgm[2] = Sound(L"AAA/BGM02.mp3");
	bgm[3] = Sound(L"AAA/BGM03.wav");
	bgm[4] = Sound(L"AAA/BGM04.mp3");
	bgm[5] = Sound(L"AAA/BGM05.mp3");
	

	se[0] = Sound(L"AAA/SE01.WAV");
	se[1] = Sound(L"AAA/SE02.WAV");
	se[2] = Sound(L"AAA/SE03.WAV");
	se[3] = Sound(L"AAA/SE04.WAV");
	se[4] = Sound(L"AAA/SE05.WAV");
	se[5] = Sound(L"AAA/SE06.WAV");
	se[6] = Sound(L"AAA/SE07.WAV");
	se[7] = Sound(L"AAA/SE08.WAV");
	se[8] = Sound(L"AAA/win.WAV");
	se[9] = Sound(L"AAA/lose.WAV");
	se[10] = Sound(L"AAA/SE09.WAV");
	se[11] = Sound(L"AAA/Bomb.WAV");
	se[12] = Sound(L"AAA/enemy.wav");

	No = -1;
	BGM = 0;
}

void SoundSE::BGMPlay(int i) {
	float Vol[10] = {
		0.8, 1.2, 1.2, 1.2, 1.2, 0.5, 0.5, 0.5, 0.5, 0.5
	};
	if (No == i)return;
	if (No != -1) {
		bgm[No].stop();
		bgm[No].setVolume(0);

	}
	bgm[i].setVolume(Vol[i]);
	if (!bgm[i].isLoop()) {
		bgm[i].setLoop(true);
	}
	bgm[i].play();
	No = i;
}

void SoundSE::SEPlay(int i) {
	float Vol[13] = {
		0.1, 0.1, 0.5, 0.1, 0.1, 0.5, 0.5, 0.5, 0.5, 0.5,0.5,0.5,0.5
	};
	if (se[i].isPlaying()) {
		se[i].stop();
		se[i].setVolume(0);
	}
	se[i].setVolume(Vol[i]);
	se[i].play();
}

int SoundSE::getBGM() {
	return BGM;
}

void SoundSE::setBGM(int n) {
	BGM = n;
}
