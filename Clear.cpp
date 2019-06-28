#include "Clear.h"



//-------------
//�R���X�g���N�^
//-------------
Clear::Clear(Koma* koma) {
	this->KM1 = koma;
	img = Texture(L"Example/clear.png");
	Timer = 3.0f;

	this->skill = skill;
}

//-------------
//����
//-------------
void Clear::UpDate() {

	Timer -= FrameTime;

	if (Timer >= 0) {
		return;//�܂����Ԃł͂Ȃ�
	}
	if (Input::MouseR.clicked) {
		//�F����1�F�ǉ�
		int n = KM1->getColorMode();
		n++;
		
		if (n > 8)n = 8;
		KM1->setColorMode(n);//1�F�ǉ�
		KM1->setGameST(0);//restart
		
		Timer = 3.0f;
	}
}

//-------------
//�\��
//-------------
void Clear::Draw() {

	if (KM1->getGameST() != 10) return;
	img.resize(1280, 960).draw(0, 0);
}