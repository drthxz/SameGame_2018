#pragma once
#include<Siv3D.hpp>
#include"SoundSE.h"


class Koma
{
private:
	
	const int Size = 80;//�ς̃��T�C�Y
	const static int Ax = 16+1;
	const static int Ay = 12;
	//��`�̐ݒ�
	Texture texture[9];
	float x, y;

	float Mouse_x, Mouse_y;
	//�ϔz�u�f�[�^
		//�������f�[�^=9
		//���̃R�[�h=-9
		//�ǂ̃R�[�h=-9

	int Koma_Flag[Ay][Ax] = { {0} };//�ċA�̌���
	int Koma_Copy[Ay][Ax] = { {0} };//�ċA�p��Koma_Data�̃R�s�[


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

	int Game_ST;//�Q�[���̗���
				//0::���Ƃ�
				//1::�������@�������؂�
				//2::�ċA
				//3::�X���C�h
				//4::�@*****

	int Color_Mode;//�F��

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

