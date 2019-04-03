#pragma once

#define _EMPTY			0
#define _FOREST			1
#define _ICE			2
#define _WALL			3
#define _RIVER			4
#define _STONE			5

#define _CX				0
#define _CY				1
#define DIR_LEFT		0
#define DIR_UP			1
#define DIR_RIGHT		2
#define DIR_DOWN		3

#define WIN_WIDTH		416*2
#define WIN_HEIGHT		416*2
#define CANVAS_WIDTH	208
#define CANVAS_HEIGT	208

#define BOX_SIZE		8
#define SMALL_BOX_SIZE  4

struct MarkBox
{
	int box_4[52][52];
	int box_8[26][26];
};

struct Map
{
	int map[26][26];
};