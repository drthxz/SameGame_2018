#pragma once
#include<Siv3D.hpp>
#include"Koma.h"
#include"SoundSE.h"
#define MAX 3




class Koma;
class Skill {
	Koma* KM1;
	const int Size = 80;//ºÏ‚ÌƒŠƒTƒCƒY
	const static int Ax = 16 + 1;
	const static int Ay = 12;
	int i = MAX;
	Font f = Font(16);

	const float FrameTime = 1.0f / 60.0f;
	float Timer;

	Texture texture[1];

	SoundSE* SD;
public:
	Skill(Koma*koma, SoundSE* sound);
	void Bomb();
	void Reset();
	void Enemy();

	void UpDate();
	
};