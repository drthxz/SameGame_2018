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
		if (Flag[i] != 0) {//出現の場合のみ
			x[i] += FramTime * xSpeed[i] * cos(kaku[i] * 3.141592f / 180.0f);
			y[i] += FramTime * ySpeed[i] * sin(kaku[i] * 3.141592f / 180.0f);
			
			//動く先が床ORｺﾏなら書き換え
			if (y[i] > 0 && Flag[i] == 1) {//画面外は無視
				//座標から2次元配列の何行何列に変換
				int xx = (x[i]+Size/2+Size)/Size;//x[i]の点は写真の左 +半分のSIZEは点が写真の真ん中になる　/ｺﾏのSIZEになると一枚一枚で計算できる
				int yy = (y[i]+Size)/Size;
				int nn =KM1->getKoma(xx,yy);
				if (nn != 9) {//2次元配列に書き換え
					Flag[i] = 0;
					KM1->setKoma(xx, yy - 1, CNo[i]);//=CNo[i]
				}
			}
			if (Flag[i] == 2) {

				
				int xx = (x[i] + Size) / Size;
				int yy = y[i] / Size;
				int nn = KM1->getKoma(xx, Ay-2);

				if (nn != 9 ) {//2次元配列に書き換え
					
					Flag[i] = 0;
					KM1->setKoma(xx+1, yy, CNo[i]);
					

				}
			}

		}
	}
	f1(L"X=", y[0]).draw(100, 1000 - 80);
}

//--------------
//落ち切りチェック
//戻り値::1=まだ
//        0=全部落ちた
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
// 全てを使って上から落下
//---------------
void Sprit::req() {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>ui(1, KM1->getColorMode());

	for (int i = 0; i < max; ++i) {//max=16*11=176

		//1列表示終わりなら高さを1段上げる
		if (Flag[i] == 0) {
			x[i] = (i % (Ax-1))*Size;//1,2,3,4,5,6,7,8....
			y[i] = (i / (Ax-1))*-Size;//0,0,0,0,0,0,0,0,0.......1,1,1,1,1,1,
			ySpeed[i] = 500;
			kaku[i] = 90;
			CNo[i] = ui(gen);//キャラ番号(乱数で決定）
			Flag[i] = 1;
		}
	}
	
}

//------------
//下から空きを探す
//------------
void Sprit::req2() {

	//if (Input::MouseR.clicked) {
	//	int xx = (Mouse::Pos().x + Size) / Size;//何列
	//	int yy = Mouse::Pos().y / Size;//何行
	//}

	//下から空きをチェック
	for (int i = 1; i < Ax; i++) {
		for (int j = Ay - 1; j >= 0; --j) {
			if (KM1->getKoma(i, j) == 9) {//消えたコード
				req2_Set(i,j);//実際の落とすｺﾏﾘｸｴｽﾄ

			}
		}
	}
	KM1->setGameST(4);

	//落ちる音------

}

//------------
//常に空きがあるかチェック
//------------
void Sprit::req2_Set(int X,int Y) {

	//受け取った場所から上全てを落とす

	for (int j = Y; j >= 0;--j) {
		if (KM1->getKoma(X, j) != 9) {

			for (int i = 0; i < max; ++i) {//max=16*11=176

				if (Flag[i] == 0) {
					//1列表示終わりなら高さを1段上げる
					x[i] = X * Size - Size;//座標に変換
					y[i] = j * Size;
					ySpeed[i] = 500;
					xSpeed[i] = 500;
					Flag[i] = 1;
					kaku[i] = 90;
					CNo[i] = KM1->getKoma(X, j);//キャラ番号(乱数で決定）
					
					KM1->setKoma(X, j, 9);//消えたコードでコマを初期化
					break;
				}
			}
		}
	}//上まで登ります
}

//------------
//左スライド（冬休み課題）
//------------
void Sprit::req3() {
	//左から空きをチェック
	for (int i = Ax-1; i >=0; --i) {
		
			if (KM1->getKoma(i, 10) == 9) {//消えたコード
				req3_Set(i, 10);//実際の落とすｺﾏﾘｸｴｽﾄ
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
							//1列表示終わりなら高さを1段上げる
							x[k] = j * Size - Size;//座標に変換
							y[k] = i * Size;
							ySpeed[k] = 500;
							xSpeed[k] = 500;
							Flag[k] = 2;
							kaku[k] = 180;
							CNo[k] = KM1->getKoma(j, i);//キャラ番号(乱数で決定）

							KM1->setKoma(j, i, 9);//消えたコードでコマを初期化
							break;
						}
					}
					
					
				}
			}
		//}
	}//上まで登ります
}

void Sprit::draw() {

	for (int i = 0; i<max; ++i) {
		if (Flag[i] != 0) {
			texture[CNo[i]].resize(Size, Size).draw(x[i], y[i]);
			
		}
	}

	
}