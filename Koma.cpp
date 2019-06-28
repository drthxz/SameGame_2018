#include "Koma.h"
#include "SoundSE.h"


Koma::Koma(SoundSE * sound)
{

	texture[0] = Texture(L"AAA/0.png");
	texture[1] = Texture(L"AAA/1.png");
	texture[2] = Texture(L"AAA/2.png");
	texture[3] = Texture(L"AAA/3.png");
	texture[4] = Texture(L"AAA/4.png");
	texture[5] = Texture(L"AAA/5.png");
	texture[6] = Texture(L"AAA/6.png");
	texture[7] = Texture(L"AAA/7.png");
	texture[8] = Texture(L"AAA/0.png");
	
	x = -Size;//-80�ɒ�`����
	y = 0;

	Color_Mode = 2;//2�F���[�h����X�^�[�g
	Game_ST = 0;
	Init();//2�����z���������
	this->SD = sound;


}
//-----------
//�R�}������
//-----------
void Koma::Init() {
	//2�����z����������ނŖ��߂�
	for (int i = 0; i < Ax; i++) {
		for (int j = 0; j < Ay - 1; j++) {
			Koma_Data[j][i] = 9;//��������
		}
	}
	//�����ސ���
	for (int i = 0; i < Ax; i++) {
		Koma_Data[Ay - 1][i] = -9;//������
	}
	//�Ǻ��ސ���
	for (int i = 0; i < Ay; i++) {
		Koma_Data[i][0] = -9;
	}
}

//-----
//�S����������
//�߂�l::9=�S��������
//		�@1=�܂��R�}���c���Ă���
//-----
int Koma::Clear_chk() {
	int ok = 9;

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 12; j++) {

			int n = Koma_Data[j][i];
			if (n > 0 && n < 9) {
				ok = 1;
				break;
			}
		}
	}
	return ok;
}

//-----
//�S����������
//�߂�l::9=�����Ȃ�----gameover!
//		�@1=������
//-----
int Koma::saiki_ok() {
	int ok, count;
	ok = 0;
	count = 0;

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 12; j++) {

			if (Koma_Flag[j][i] == 1) {
				count++;
			}
		}
	}
	//count��1��葽����������
	if (count > 1) {
		ok = 1;
	}

	return ok;
}

//-----
//�S����������
//�߂�l::9=�S��������
//		�@1=�܂��R�}���c���Ă���
//-----
int Koma::Over_chk() {
	int ok = 9;

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 12; j++) {

			int n = Koma_Data[j][i];
			if (n > 0 && n < 9) {
				Saiki_Init();
				Fill_All(Koma_Copy, Koma_Flag, i, j, n);

				
				if (saiki_ok() == 1) {
					ok = 1;
					break;
				}//�ċA�ŏ�����H
			}
		}
	}
	return ok;
}



void Koma::upData() {

	
	if (Clear_chk() == 9) {
		Game_ST = 10;
		SD->BGMPlay(0);
		SD->SEPlay(8);
		//Cl->SetTimer(2f);
		return;
	}

	if (Over_chk() == 9) {
		Game_ST = 11;
		SD->BGMPlay(0);
		SD->SEPlay(9);
		//Cl->SetTimer(2f);
		return;
	}


	//ϳ�
	Mouse_x = Mouse::Pos().x;
	Mouse_y = Mouse::Pos().y;

	//ϳ����W�����s����
	int xx = (Mouse_x+Size)/Size;
	int yy = Mouse_y/Size;
	int nn = Koma_Data[yy][xx];
	if (nn < 0 || nn>9)return;//�σf�[�^�ȊO�͍ċA�R�[�����Ȃ�

	Saiki_Init();
	Fill_All(Koma_Copy, Koma_Flag, xx, yy, nn);
	Del_Chk();
	Del();


}

void Koma::draw() {
	for (int i = 0;i < Ax;i++) {
		for (int j = 0;j < Ay;j++) {
			int n = Koma_Data[j][i];
			
			if (n == 9)continue;
			int al = 255;
			if (Koma_Flag[j][i] == 1)al = 150;//�ċA�ŕ���OK�Ȃ甼����
			//�������H�ǁH���H
			if (n>0) {
				texture[n].resize(Size, Size).draw(x + Size * i, y + Size * j, Alpha(al));//Alpha=255��max
			}
		}
	}
	
}

//------------
//ٰ�::2�ȏ�͏�����
//------------
void Koma::Del_Chk() {
	int cnt;
	int x;
	int y;
	cnt = 0;
	for (int i = 0; i < Ax; i++) {
		for (int j = 0; j < Ay; j++) {
			if (Koma_Flag[j][i] == 1) {
				cnt++;
				y = j;
				x = i;
			}
		}
	}
	if (cnt == 1) {
		//����1���N���A--------
		Koma_Flag[y][x] = 0;
	}
	
}





//-------------
//����
//-------------
void Koma::Del() {
	if (Input::MouseL.clicked) {
		int seChange = 0, i = Koma_Data[(Mouse::Pos().y / Size) % (Ay - 1)][Mouse::Pos().x / Size + 1];
		for (int i = 0; i < Ax; i++) {
			for (int j = 0; j < Ay; j++) {

				if (Koma_Flag[j][i] == 1) {
					seChange = 1;
					Game_ST = 3;//���Ƃ�
					Koma_Flag[j][i] = 0;
					Koma_Data[j][i] = 9;//�������R�[�h
					
				}
			}
		}
		if(seChange ==1)SD->SEPlay(i);
	}


}


int Koma::getColorMode() {
	return Color_Mode;
}

void Koma::setColorMode(int n) {
	Color_Mode = n;
}



//GET������Ȃ�A�K��SET������
//-------------
//�R�}�f�[�^GET�@getGameST()
//-------------
int Koma::getGameST() {
	return Game_ST;

}


//-------------
//�R�}�f�[�^SET�@setGameST()
//-------------
void Koma::setGameST(int n) {
	Game_ST=n;
}

//-------------
//�R�}�f�[�^GET
//-------------
int Koma::getKoma(int xx, int yy) {
	return Koma_Data[yy][xx];
}

//-------------
//�R�}�f�[�^SET
//-------------
void Koma::setKoma(int xx, int yy, int nn) {
	Koma_Data[yy][xx] = nn;
}


//---------
//�㉺���E�̑�������
//����::no=�����ԍ���T��
//	  ::f[][]==�������тȂ�1
//---------
void Koma::Fill_All(int d[][Ax], int f[][Ax], int ix, int iy, int no) {

	if (ix < 0 || ix>(Ax - 1) || iy<0 || iy>(Ay - 1)) return;
	else {

		d[iy][ix] = -8;//�K���`�F�b�Nend  //���߂�
		if (d[iy][ix - 1] == no)Fill_All(d, f, ix - 1, iy, no);//��
		if (d[iy][ix + 1] == no)Fill_All(d, f, ix + 1, iy, no); //�E

		if (d[iy - 1][ix] == no)Fill_All(d, f, ix, iy - 1, no);//��
		if (d[iy + 1][ix] == no)Fill_All(d, f, ix, iy + 1, no);//��

															   //���т�okflag set

		f[iy][ix] = 1;//����ł܂�

	}
}
//----------------
//�ċA�p�̏�����
//Koma_Data->Koma_Copy
//Koma_Flag->0
//----------------
void Koma::Saiki_Init() {
	for (int i = 0; i < Ax; i++) {
		for (int j = 0; j < Ay; j++) {
			Koma_Copy[j][i] = Koma_Data[j][i];
			Koma_Flag[j][i] = 0;

		}
	}
}