#pragma once
# include <Siv3D.hpp>
#include"Koma.h"

//-------
//�Q�[���I�[�o�[
//-------
class Koma;
class Over {
	Texture img;
	Koma* KM1;

	const float FrameTime = 1.0f / 60.0f;
	float Timer;//�ȑ҂�  

public:
	Over(Koma*);
	void UpDate();
	void Draw();
};