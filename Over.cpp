#include "Over.h"




//-------------
//コンストラクタ
//-------------
Over::Over(Koma* koma) {
	KM1 = koma;
	img = Texture(L"Example/over.png");

	Timer = 3.0f;
}

//-------------
//処理
//-------------
void Over::UpDate() {
	Timer -= FrameTime;

	if (Timer >= 0) {
		return;//まだ時間ではない
	}

	if (Input::MouseR.clicked) {
		KM1->Init();
		KM1->setColorMode(2);
		KM1->setGameST(0);//restart
	}
}

//-------------
//表示
//-------------
void Over::Draw() {
	if (KM1->getGameST() != 11) return;
	img.resize(1280, 960).draw(0, 0,Alpha(150));
}