#include"Skill.h"




Skill::Skill(Koma*koma, SoundSE* sound) {
	this->KM1 = koma;
	this->SD = sound;


	texture[0] = Texture(L"AAA/enemy.png");
	Timer = 60.0f;
}


void Skill::UpDate() {
	Timer -= FrameTime;

	Bomb();

	if (Timer >=20) {
		//Enemy();
		return;//まだ時間ではない
	}
	else {
		//Enemy();
		
	}

	
}

void Skill::Reset() {
	i = 3;
}

//------------
//ボム
//------------
void Skill::Bomb() {
	if (i != 0) {
		
		if (Input::MouseR.clicked) {
			int posX = (Mouse::Pos().x / Size + 1);
			int posY = (Mouse::Pos().y / Size) % (Ay - 1);
			i--;
			for (int x = -1; x < 2; x++) {
				for (int y = -1; y < 2; y++) {
					if(posX +x>0 &&y+ posY <Ay-1)
					KM1->setKoma(posX + x, posY + y, 9);
					SD->SEPlay(12);
				}
			}
			
			KM1->setGameST(3);
		}
	}
	f(L"右クリックするとスキル使用可能").draw(360, 960 - 80);
	f(L"ボム:",i).draw(360, 960 - 40);
	f(L"Time:", Timer).draw(1080, 960 - 40);

	//f(L"[", (Mouse::Pos().y / 80) % (12 - 1), L":", Mouse::Pos().x / 80 + 1, L"}").draw(Mouse::Pos());
}

//---------
//敵
//---------
void Skill::Enemy() {

	
	int count = 0;
	
	texture[0].resize(Size,Size).draw(Mouse::Pos().x + Size , Mouse::Pos().y + Size);

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 12; j++) {

			if (KM1->getKoma(i,j) == 1) {
				count++;
			}
		}
	}
	f(L"count:",count).draw(950,1000-30);
	f(L"D:drag  x",Timer);

}

