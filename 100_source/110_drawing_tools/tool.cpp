//-----------------------------
// @name   tool.cpp
// @brief  ツール系関数の実装部
// @auther A.namami
// @date   2026/2/4  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include <cmath>
#include "tool.h"

void CrampInt(int& param, int low, int max)
{
	if (param < low) {
		param = low;
	}
	else if(param>max) {
		param = max;
	}
}

void CrampFloat(float& param, float low, float max)
{
	if (param < low) {
		param = low;
	}
	else if (param > max) {
		param = max;
	}
}

void CrampDouble(double& param, double low, double max)
{
	if (param < low) {
		param = low;
	}
	else if (param > max) {
		param = max;
	}
}

bool InRenge(int param, int low, int max)
{
	//範囲外か
	if (param < low || max < param) { return false; }

	return true;
}

int Abs(int param)
{
	int returner = param;
	//負の数か
	if (param < 0) {
		returner = -param;
	}

	return returner;
}

void ChangeColorToRgb(const unsigned int color_code, int& red, int& green, int& blue)
{
	/*理論
	* 16進数毎に取り出して10進数に変換
	*/
	//それぞれの要素を取り出す
	unsigned int red_16 = color_code >> 16;
	unsigned int green_16 = (color_code >> 8) - (red_16 << 8);
	unsigned int blue_16 = color_code - (red_16 << 16) -(green_16<<8);
	//入れればOK
	red = red_16;
	green = green_16;
	blue = blue_16;
}

unsigned int ChangeColorToCode(int red, int green, int blue)
{
	//とりあえず左シフト
	unsigned int red_16 = red << 16;
	unsigned int green_16 = green << 8;
	unsigned int blue_16 = blue;

	//ひたすら足す

	return red_16+green_16+blue_16;
}

bool AlmostEqual(double a, double b, double epsilon)
{
	return std::fabs(a - b) < epsilon;
}

int ChangeBitToNum(int flg)
{
	//0以下ならそもそもフラグではないので突き返す
	if (flg <= 0) {
		return -1;
	}
	int i = 0;//返り値
	while (true) {
		//フラグが見つかるか
		if ((flg >> i) & 1) {
			break;
		}
		i++;
	}
	return i;
}
