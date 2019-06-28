#pragma once
#include<Siv3D.hpp>
#include"Koma.h"
#include"SoundSE.h"
//--------------
//　落ちるとスライド
//--------------

class Koma;
class Sprit {

	Koma* KM1;
	SoundSE * SD;
	const int Size = 80;//ｺﾏのリサイズ
	const static int Ax = 16 + 1;
	const static int Ay = 11+1;

	const static int max = (Ax - 1)*(Ay - 1);
	
	Texture texture [8];
	Sound bgm[5];
	Sound se[5];
	float x[max] = { 0 };
	float y[max] = { 0 };
	Font f1 = Font(15);
	float kaku[max] = { 0 };
	float ySpeed[max] = { 0 };
	float xSpeed[max] = { 0 };
	const float FramTime = 1.0f/60.0f;
	float Flag[max] = {0};
	int CNo[max] = { 0 };//表示キャラ



public:
	Sprit(Koma *koma,SoundSE *sound);

	void draw();
	void UpData();
	void req();
	void req2();
	void req2_Set(int X,int Y);
	int Down_Chk();
	void req3();
	void req3_Set(int X, int Y);
};