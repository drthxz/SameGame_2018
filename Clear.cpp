#include "Clear.h"



//-------------
//コンストラクタ
//-------------
Clear::Clear(Koma* koma) {
	this->KM1 = koma;
	img = Texture(L"Example/clear.png");
	Timer = 3.0f;

	this->skill = skill;
}

//-------------
//処理
//-------------
void Clear::UpDate() {

	Timer -= FrameTime;

	if (Timer >= 0) {
		return;//まだ時間ではない
	}
	if (Input::MouseR.clicked) {
		//色数を1色追加
		int n = KM1->getColorMode();
		n++;
		
		if (n > 8)n = 8;
		KM1->setColorMode(n);//1色追加
		KM1->setGameST(0);//restart
		
		Timer = 3.0f;
	}
}

//-------------
//表示
//-------------
void Clear::Draw() {

	if (KM1->getGameST() != 10) return;
	img.resize(1280, 960).draw(0, 0);
}