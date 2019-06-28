#pragma once
#include<Siv3D.hpp>
#include"SoundSE.h"


class Koma
{
private:
	
	const int Size = 80;//ｺﾏのリサイズ
	const static int Ax = 16+1;
	const static int Ay = 12;
	//定義の設定
	Texture texture[9];
	float x, y;

	float Mouse_x, Mouse_y;
	//ｺﾏ配置データ
		//消えたデータ=9
		//床のコード=-9
		//壁のコード=-9

	int Koma_Flag[Ay][Ax] = { {0} };//再帰の結果
	int Koma_Copy[Ay][Ax] = { {0} };//再帰用のKoma_Dataのコピー


	int Koma_Data[Ay][Ax] = {
	{-9, 0,1,2,3,4,5,6,7, 8,1,2,3,0,5,6,7, },
	{-9, 8,0,2,3,4,5,6,7, 8,1,2,0,4,5,6,7, },
	{-9, 8,1,0,3,4,5,6,7, 8,1,0,3,4,5,6,7, },
	{-9, 8,1,2,0,4,5,6,7, 8,0,2,3,4,5,6,7, },
	{-9, 8,1,2,3,0,5,6,7, 0,1,2,3,4,5,6,7, },

	{-9, 8,1,2,3,4,0,6,7, 8,1,2,3,4,5,6,7, },
	{-9, 8,1,2,3,4,5,0,7, 8,1,2,3,4,5,6,7, },
	{-9, 8,1,2,3,4,5,6,7, 8,1,2,3,4,5,6,7, },
	{-9, 8,1,2,3,4,5,6,7, 8,1,2,3,4,5,6,7, },
	{-9, 8,1,2,3,4,5,6,7, 8,1,2,3,4,5,6,7, },

	{-9, 8,1,2,3,4,5,6,7, 8,1,2,3,4,5,6,7, },
	{-9, -9,-9,-9,-9,-9,-9,-9,-9, -9,-9,-9,-9,-9,-9,-9,-9, },
	};

	int Game_ST;//ゲームの流れ
				//0::落とす
				//1::動かす　＆落ち切り
				//2::再帰
				//3::スライド
				//4::　*****

	int Color_Mode;//色数

	SoundSE *SD;
	

public:
	Koma(SoundSE * sound);
	void Init();
	void upData();
	void draw();
	int getKoma(int xx, int yy);
	void setKoma(int xx, int yy, int nn);
	void Fill_All(int d[][Ax], int f[][Ax], int ix, int iy, int no);
	void Saiki_Init();

	void Del_Chk();
	void Del();
	int getGameST();
	void setGameST(int n);

	int getColorMode();
	void setColorMode(int n);

	int Clear_chk();
	int Over_chk();
	int saiki_ok();

};

