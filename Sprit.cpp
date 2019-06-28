#include "Sprit.h"

#include <iostream>
using namespace std;




Sprit::Sprit(Koma *koma, SoundSE *sound) {

	this->KM1= koma;
	texture[0] = Texture(L"AAA/0.png");
	texture[1] = Texture(L"AAA/1.png");
	texture[2] = Texture(L"AAA/2.png");
	texture[3] = Texture(L"AAA/3.png");
	texture[4] = Texture(L"AAA/4.png");
	texture[5] = Texture(L"AAA/5.png");
	texture[6] = Texture(L"AAA/6.png");
	texture[7] = Texture(L"AAA/7.png");

	this->SD = sound;
	bgm[0] = Sound(L"AAA/BGM01.wav");
	bgm[1] = Sound(L"AAA/BGM02.mp3");
	bgm[2] = Sound(L"AAA/BGM03.wav");
	bgm[3] = Sound(L"AAA/BGM04.mp3");
	bgm[4] = Sound(L"AAA/BGM05.mp3");

	se[0] = Sound(L"AAA/SE01.WAV");
	se[1] = Sound(L"AAA/SE02.WAV");
	se[2] = Sound(L"AAA/SE03.WAV");
	se[3] = Sound(L"AAA/SE04.WAV");


}




void Sprit::UpData() {

	
	for (int i = 0; i < max; ++i) {
		if (Flag[i] != 0) {//�o���̏ꍇ�̂�
			x[i] += FramTime * xSpeed[i] * cos(kaku[i] * 3.141592f / 180.0f);
			y[i] += FramTime * ySpeed[i] * sin(kaku[i] * 3.141592f / 180.0f);
			
			//�����悪��OR�ςȂ珑������
			if (y[i] > 0 && Flag[i] == 1) {//��ʊO�͖���
				//���W����2�����z��̉��s����ɕϊ�
				int xx = (x[i]+Size/2+Size)/Size;//x[i]�̓_�͎ʐ^�̍� +������SIZE�͓_���ʐ^�̐^�񒆂ɂȂ�@/�ς�SIZE�ɂȂ�ƈꖇ�ꖇ�Ōv�Z�ł���
				int yy = (y[i]+Size)/Size;
				int nn =KM1->getKoma(xx,yy);
				if (nn != 9) {//2�����z��ɏ�������
					Flag[i] = 0;
					KM1->setKoma(xx, yy - 1, CNo[i]);//=CNo[i]
				}
			}
			if (Flag[i] == 2) {

				
				int xx = (x[i] + Size) / Size;
				int yy = y[i] / Size;
				int nn = KM1->getKoma(xx, Ay-2);

				if (nn != 9 ) {//2�����z��ɏ�������
					
					Flag[i] = 0;
					KM1->setKoma(xx+1, yy, CNo[i]);
					

				}
			}

		}
	}
	f1(L"X=", y[0]).draw(100, 1000 - 80);
}

//--------------
//�����؂�`�F�b�N
//�߂�l::1=�܂�
//        0=�S��������
//--------------
int Sprit::Down_Chk() {
	int ok;
	ok = 0;

	for (int i = 0; i < max; i++) {
		if (Flag[i] != 0) {
			ok = 1;
			break;
		}
	}
	return ok;
}



//---------------
// �S�Ă��g���ďォ�痎��
//---------------
void Sprit::req() {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>ui(1, KM1->getColorMode());

	for (int i = 0; i < max; ++i) {//max=16*11=176

		//1��\���I���Ȃ獂����1�i�グ��
		if (Flag[i] == 0) {
			x[i] = (i % (Ax-1))*Size;//1,2,3,4,5,6,7,8....
			y[i] = (i / (Ax-1))*-Size;//0,0,0,0,0,0,0,0,0.......1,1,1,1,1,1,
			ySpeed[i] = 500;
			kaku[i] = 90;
			CNo[i] = ui(gen);//�L�����ԍ�(�����Ō���j
			Flag[i] = 1;
		}
	}
	
}

//------------
//������󂫂�T��
//------------
void Sprit::req2() {

	//if (Input::MouseR.clicked) {
	//	int xx = (Mouse::Pos().x + Size) / Size;//����
	//	int yy = Mouse::Pos().y / Size;//���s
	//}

	//������󂫂��`�F�b�N
	for (int i = 1; i < Ax; i++) {
		for (int j = Ay - 1; j >= 0; --j) {
			if (KM1->getKoma(i, j) == 9) {//�������R�[�h
				req2_Set(i,j);//���ۂ̗��Ƃ���ظ���

			}
		}
	}
	KM1->setGameST(4);

	//�����鉹------

}

//------------
//��ɋ󂫂����邩�`�F�b�N
//------------
void Sprit::req2_Set(int X,int Y) {

	//�󂯎�����ꏊ�����S�Ă𗎂Ƃ�

	for (int j = Y; j >= 0;--j) {
		if (KM1->getKoma(X, j) != 9) {

			for (int i = 0; i < max; ++i) {//max=16*11=176

				if (Flag[i] == 0) {
					//1��\���I���Ȃ獂����1�i�グ��
					x[i] = X * Size - Size;//���W�ɕϊ�
					y[i] = j * Size;
					ySpeed[i] = 500;
					xSpeed[i] = 500;
					Flag[i] = 1;
					kaku[i] = 90;
					CNo[i] = KM1->getKoma(X, j);//�L�����ԍ�(�����Ō���j
					
					KM1->setKoma(X, j, 9);//�������R�[�h�ŃR�}��������
					break;
				}
			}
		}
	}//��܂œo��܂�
}

//------------
//���X���C�h�i�~�x�݉ۑ�j
//------------
void Sprit::req3() {
	//������󂫂��`�F�b�N
	for (int i = Ax-1; i >=0; --i) {
		
			if (KM1->getKoma(i, 10) == 9) {//�������R�[�h
				req3_Set(i, 10);//���ۂ̗��Ƃ���ظ���
			}
	}
	KM1->setGameST(6);
}

void Sprit::req3_Set(int X, int Y) {
	
	
	for (int j = X; j <= 16; ++j) {
		//if (KM1->getKoma(j, Y) != 9) {
			
			for (int i = 0; i < 11; ++i) {//max=16*11=176

				if (KM1->getKoma(j, i) != 9) {
					for (int k = 0; k < max; k++) {
						if (Flag[k] != 2) {
							//1��\���I���Ȃ獂����1�i�グ��
							x[k] = j * Size - Size;//���W�ɕϊ�
							y[k] = i * Size;
							ySpeed[k] = 500;
							xSpeed[k] = 500;
							Flag[k] = 2;
							kaku[k] = 180;
							CNo[k] = KM1->getKoma(j, i);//�L�����ԍ�(�����Ō���j

							KM1->setKoma(j, i, 9);//�������R�[�h�ŃR�}��������
							break;
						}
					}
					
					
				}
			}
		//}
	}//��܂œo��܂�
}

void Sprit::draw() {

	for (int i = 0; i<max; ++i) {
		if (Flag[i] != 0) {
			texture[CNo[i]].resize(Size, Size).draw(x[i], y[i]);
			
		}
	}

	
}