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
	
	x = -Size;//-80に定義する
	y = 0;

	Color_Mode = 2;//2色モードからスタート
	Game_ST = 0;
	Init();//2次元配列を初期化
	this->SD = sound;


}
//-----------
//コマ初期化
//-----------
void Koma::Init() {
	//2次元配列を消すｺｰﾄﾞで埋める
	for (int i = 0; i < Ax; i++) {
		for (int j = 0; j < Ay - 1; j++) {
			Koma_Data[j][i] = 9;//消すｺｰﾄﾞ
		}
	}
	//床ｺｰﾄﾞ制作
	for (int i = 0; i < Ax; i++) {
		Koma_Data[Ay - 1][i] = -9;//床ｺｰﾄﾞ
	}
	//壁ｺｰﾄﾞ制作
	for (int i = 0; i < Ay; i++) {
		Koma_Data[i][0] = -9;
	}
}

//-----
//全部きえたか
//戻り値::9=全部消えた
//		　1=まだコマが残っている
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
//全部きえたか
//戻り値::9=消せない----gameover!
//		　1=消せる
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
	//countが1より多き時消せる
	if (count > 1) {
		ok = 1;
	}

	return ok;
}

//-----
//全部きえたか
//戻り値::9=全部消えた
//		　1=まだコマが残っている
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
				}//再帰で消せる？
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


	//ﾏｳｽ
	Mouse_x = Mouse::Pos().x;
	Mouse_y = Mouse::Pos().y;

	//ﾏｳｽ座標を何行何列
	int xx = (Mouse_x+Size)/Size;
	int yy = Mouse_y/Size;
	int nn = Koma_Data[yy][xx];
	if (nn < 0 || nn>9)return;//ｺﾏデータ以外は再帰コールしない

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
			if (Koma_Flag[j][i] == 1)al = 150;//再帰で並びOKなら半透明
			//消えた？壁？床？
			if (n>0) {
				texture[n].resize(Size, Size).draw(x + Size * i, y + Size * j, Alpha(al));//Alpha=255でmax
			}
		}
	}
	
}

//------------
//ﾙｰﾙ::2個以上は消せる
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
		//その1をクリア--------
		Koma_Flag[y][x] = 0;
	}
	
}





//-------------
//消す
//-------------
void Koma::Del() {
	if (Input::MouseL.clicked) {
		int seChange = 0, i = Koma_Data[(Mouse::Pos().y / Size) % (Ay - 1)][Mouse::Pos().x / Size + 1];
		for (int i = 0; i < Ax; i++) {
			for (int j = 0; j < Ay; j++) {

				if (Koma_Flag[j][i] == 1) {
					seChange = 1;
					Game_ST = 3;//落とせ
					Koma_Flag[j][i] = 0;
					Koma_Data[j][i] = 9;//消えたコード
					
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



//GETがあるなら、必ずSETがある
//-------------
//コマデータGET　getGameST()
//-------------
int Koma::getGameST() {
	return Game_ST;

}


//-------------
//コマデータSET　setGameST()
//-------------
void Koma::setGameST(int n) {
	Game_ST=n;
}

//-------------
//コマデータGET
//-------------
int Koma::getKoma(int xx, int yy) {
	return Koma_Data[yy][xx];
}

//-------------
//コマデータSET
//-------------
void Koma::setKoma(int xx, int yy, int nn) {
	Koma_Data[yy][xx] = nn;
}


//---------
//上下左右の総当たり
//引数::no=同じ番号を探す
//	  ::f[][]==同じ並びなら1
//---------
void Koma::Fill_All(int d[][Ax], int f[][Ax], int ix, int iy, int no) {

	if (ix < 0 || ix>(Ax - 1) || iy<0 || iy>(Ay - 1)) return;
	else {

		d[iy][ix] = -8;//訪問先チェックend  //埋める
		if (d[iy][ix - 1] == no)Fill_All(d, f, ix - 1, iy, no);//左
		if (d[iy][ix + 1] == no)Fill_All(d, f, ix + 1, iy, no); //右

		if (d[iy - 1][ix] == no)Fill_All(d, f, ix, iy - 1, no);//上
		if (d[iy + 1][ix] == no)Fill_All(d, f, ix, iy + 1, no);//下

															   //並びのokflag set

		f[iy][ix] = 1;//並んでます

	}
}
//----------------
//再帰用の初期化
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