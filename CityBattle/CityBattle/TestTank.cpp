#include "TestTank.h"
#include "struct.h"

int TestTank::mDPXY[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };


TestTank::TestTank(MarkBox* b)
{
	char c[50];
	mTankX = CANVAS_WIDTH/2;
	mTankY = CANVAS_HEIGT/2;
	mDir = DIR_UP;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
		{
			_stprintf_s(c, "./res/big/%dPlayer/m%d-%d-%d.gif", 0, 0, i, j + 1);
			loadimage(&mTankImage[i][j], c);
		}
	mbp = b;
	for(int i=0;i<26;i++)
		for (int j = 0; j < 26; j++)
			Fill_4(i, j, b->box_8[i][j]);
}

TestTank::TestTank(int x, int y)
{
	char c[50];
	mTankX = x;
	mTankY = y;
	mDir = DIR_UP;
	for(int i=0;i<4;i++)
		for (int j = 0; j < 2; j++)
		{
			_stprintf_s(c, "./res/big/%dPlayer/m%d-%d-%d.gif", 0, 0, i, j);
			loadimage(&mTankImage[i][j], c);
		}
}

void TestTank::DrawTank(const HDC & canvas)
{
	TransparentBlt(canvas, mTankX - BOX_SIZE, mTankY - BOX_SIZE, BOX_SIZE * 2, BOX_SIZE * 2, GetImageHDC(&mTankImage[mDir][0]), 0, 0, BOX_SIZE * 2, BOX_SIZE * 2, 0x000000);
}

void TestTank::Move(int new_dir)
{


	if (mDir != new_dir)
	{
		mDir = new_dir;
	}
	else if(CheckMoveable())
	{
		mTankX += mDPXY[mDir][_CX];
		mTankY += mDPXY[mDir][_CY];
	}
}

bool TestTank::CheckMoveable()
{
	int tempx = mTankX + mDPXY[mDir][_CX];
	int tempy = mTankY + mDPXY[mDir][_CY];

	//边界检测
	if (tempx<BOX_SIZE || tempy<BOX_SIZE || tempx>CANVAS_WIDTH - BOX_SIZE || tempy>CANVAS_HEIGT - BOX_SIZE)
	{
		switch (mDir)
		{
		case DIR_LEFT:	mTankX = mTankX / BOX_SIZE * BOX_SIZE; break;
		case DIR_UP:	mTankY = mTankY / BOX_SIZE * BOX_SIZE; break;
		case DIR_RIGHT:	mTankX = mTankX / BOX_SIZE * BOX_SIZE; break;
		case DIR_DOWN:	mTankY = mTankY / BOX_SIZE * BOX_SIZE; break;
		default:break;
		}
		return false;
	}
	//障碍物检测

	int xi = tempx / SMALL_BOX_SIZE;
	int yj = tempy / SMALL_BOX_SIZE;

		/*if (tempx - tempx / SMALL_BOX_SIZE * SMALL_BOX_SIZE < SMALL_BOX_SIZE / 2)
			xi = tempx / SMALL_BOX_SIZE;
		else
			xi = tempx / SMALL_BOX_SIZE + SMALL_BOX_SIZE;
		if (tempy - tempy / SMALL_BOX_SIZE * SMALL_BOX_SIZE < SMALL_BOX_SIZE / 2)
			yj = tempy / SMALL_BOX_SIZE;
		else
			yj = tempy / SMALL_BOX_SIZE + SMALL_BOX_SIZE;*/

	int dev_4[4][4][2] = { {{-2,-2},{-2,-1},{-2,0},	{-2,1}},
							{{1,-2},{0,-2},	{-1,-2},{-2,-2}},
							{{1,1},	{1,0},	{1,-1},	{1,-2}},
							{{-2,1},{-1,1},	{0, 1},	{1,1}} };
	bool temp1, temp2, temp3, temp4;
	temp1 = mbp->box_4[yj + dev_4[mDir][0][_CY]][xi + dev_4[mDir][0][_CX]] < _WALL;
	temp2 = mbp->box_4[yj + dev_4[mDir][1][_CY]][xi + dev_4[mDir][1][_CX]] < _WALL;
	temp3 = mbp->box_4[yj + dev_4[mDir][2][_CY]][xi + dev_4[mDir][2][_CX]] < _WALL;
	temp4 = mbp->box_4[yj + dev_4[mDir][3][_CY]][xi + dev_4[mDir][3][_CX]] < _WALL;
	
	if (!temp1 || !temp2 || !temp3 || !temp4)
	{
		/*switch (mDir)
		{
			case DIR_LEFT:	mTankX = mTankX / SMALL_BOX_SIZE * SMALL_BOX_SIZE + SMALL_BOX_SIZE; break;
			case DIR_UP:	mTankY = mTankY / SMALL_BOX_SIZE * SMALL_BOX_SIZE + SMALL_BOX_SIZE; break;
			case DIR_RIGHT:	mTankX = mTankX / SMALL_BOX_SIZE * SMALL_BOX_SIZE; break;
			case DIR_DOWN:	mTankY = mTankY / SMALL_BOX_SIZE * SMALL_BOX_SIZE; break;
			default:break;
		}*/
		std::cout << '(' << xi << ',' << yj << ')' << std::endl;
		std::cout << '(' << mTankX << ',' << mTankY << ')' << std::endl;
		std::cout << temp1 << ' ' << temp2 << ' ' << temp3 << ' ' << temp4 << ' ' << std::endl;
		return false;
	}

	return true;
}

void TestTank::PlayerControl()
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		Move(DIR_UP);
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		Move(DIR_DOWN);
	}
	else if (GetAsyncKeyState('A') & 0x8000)
	{
		Move(DIR_LEFT);
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		Move(DIR_RIGHT);
	}
}

void TestTank::ShowBox()
{
	int i, j;
	for (i = 0; i < 52; i++)
	{
		for (j = 0; j < 52; j++)
			std::cout << mbp->box_4[i][j];
		std::cout << std::endl;
	}
}

IMAGE TestTank::GetTankImage(int dir, int index)
{
	return mTankImage[dir][index];
}

void TestTank::Fill_4(int i, int j, int fval)
{
	for (int k = 0; k < 2; k++)
		for (int l = 0; l < 2; l++)
			mbp->box_4[i*2+k][j*2+l] = fval;
}
