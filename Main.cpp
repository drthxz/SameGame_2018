
# include <Siv3D.hpp>
#include"Koma.h"
#include"Sprit.h"
#include "Over.h"
#include "Clear.h"
#include "SoundSE.h"
#include "Skill.h"

#define W 1280
#define H 960

void Main()
{
	Graphics::SetBackground(Palette::Darkgreen);
	Window::Resize(W, H);
	const Font font(30);
	
	
	SoundSE* SD = new SoundSE();

	
	Koma* koma = new Koma(SD);
	Clear* CL = new Clear(koma);
	Sprit* sprit = new Sprit(koma, SD);

	Over* OV = new Over(koma);

	Skill*skill = new Skill(koma, SD);
	//koma->Init();
	while (System::Update())
	{
	
		switch (koma->getGameST()) {
		case 0:
			sprit->req();
			koma->setGameST(1);
			SD->SEPlay(10);
			skill->Reset();
			break;

		case 1:
			sprit->UpData();
			if (sprit->Down_Chk()==0) {
				koma->setGameST(2);
				SD->BGMPlay(1);
			}
			break;
		case 2:
			koma->upData();
			break;
		//落とす
		case 3:
			sprit->req2();
			break;
		case 4:
			sprit->UpData();
			if (sprit->Down_Chk() == 0) {
				koma->setGameST(5);
			}
			break;
		//スライド
		case 5:
			sprit->req3();
			break;
		case 6:
			sprit->UpData();
			if (sprit->Down_Chk() == 0) {
				koma->setGameST(2);
			}
			break;
		//clear
		case 10:
			CL->UpDate();
			break;
		//over
		case 11:
			OV->UpDate();
			break;

		default:
			break;
		}

		//koma->upData();
		koma->draw();

		//sprit->upData();
		
		sprit->draw();

		CL->Draw();
		OV->Draw();
		if (koma->getGameST()<10) {
			skill->UpDate();
		}
		

		font(L"ｻﾒｶﾒ").draw(10, 960-80);
		//font(L"[", (Mouse::Pos().y / 80) % (12 - 1), L":", Mouse::Pos().x / 80 + 1, L"}").draw(Mouse::Pos());
		//Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });

	}
}
