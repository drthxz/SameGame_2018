#pragma once
#include<Siv3D.hpp>
//#define Max 5



class SoundSE
{
private:
	const static int Max = 6;
	Sound bgm[Max];
	Sound se[13];
	int No;
	int BGM;
public:
	SoundSE();
	void BGMPlay(int i);
	void SEPlay(int i);
	int getBGM();
	void setBGM(int n);
};

