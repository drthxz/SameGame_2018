#pragma once
# include <Siv3D.hpp>
#include"Koma.h"
#include"Skill.h"

//-------
//ÉQÅ[ÉÄclear
//-------
class Koma;
class Clear {
	const float FrameTime = 1.0f / 60.0f;

	Texture img;
	Koma* KM1;
	SoundSE* SD;
	float Timer;//ã»ë“Çø  

	Skill*skill;

public :
	Clear(Koma*koma);
	void UpDate();
	void Draw();


};