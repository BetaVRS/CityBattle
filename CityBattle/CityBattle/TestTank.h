#pragma once
#include "struct.h"
#include "stdafx.h"

class TestTank
{
public:
	TestTank(MarkBox* b);
	TestTank(int x, int y);

	void DrawTank(const HDC &canvas);
	void Move(int new_dir);
	bool CheckMoveable();
	void PlayerControl();
	void ShowBox();


private:
	MarkBox *mbp;
	int mTankX, mTankY;
	int mImgX, mImgY;
	unsigned char mDir : 2;
	static int mDPXY[4][2];
	IMAGE mTankImage[4][2];
private:
	IMAGE GetTankImage(int dir, int index);
	void Fill_4(int i, int j, int fval);
};
