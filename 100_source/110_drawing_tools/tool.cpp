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
#include <windows.h>
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

bool InRenge2(float param, float a, float b)
{
	float low, max;
	//小さい方をlow,大きい方をmaxに
	if (a > b) {
		max = a;
		low = b;
	}
	else {
		max = b;
		low = a;
	}

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

unsigned int ChangeColorToCode(int red, int green, int blue,int color_bit)
{
	
	//とりあえず左シフト
	unsigned int red_16 = red << 16;
	unsigned int green_16 = green << 8;
	unsigned int blue_16 = blue;

	//ひたすら足す
	//32bitスケールだとalphaが入る
	if (color_bit == 32) {
		return ((255 << 24)|red_16 | green_16 | blue_16);
	}
	//違うなら入れない
	return (red_16|green_16|blue_16);
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

// UTF-8 -> Shift-JIS 
std::string ToShiftJis(const char* utf8) {
//  存在しなければ空白で返す
	if (!utf8) return "";

	//変換に必要なバイナリサイズの計測
	int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
//  なければ空白で返す
	if (wlen == NULL) return "";

	//初期化（バイナリファイル保管用）
	std::wstring wstr(wlen, 0);
	//utf-16を経由
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, &wstr[0], wlen);
	
	//変換に必要なバイナリサイズの計測
	int slen = WideCharToMultiByte(932, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
//  なければ空白で返す
	if (slen == NULL) return "";

	//結果保管用
	std::string result(slen, 0);
	//Shift-Jisに
	WideCharToMultiByte(932, 0, wstr.c_str(), -1, &result[0], slen, NULL, NULL);
	
	return result.c_str(); // const char*化して返す
}

std::string ToUtf8(const char* sift_jis)
{

	//  存在しなければ空白で返す
	if (!sift_jis) return "";

	//変換に必要なバイナリサイズの計測
	int wlen = MultiByteToWideChar(932, 0, sift_jis, -1, NULL, 0);
	//  なければ空白で返す
	if (wlen == NULL) return "";

	//初期化（バイナリファイル保管用）
	std::wstring wstr(wlen, 0);
	//utf-16を経由
	MultiByteToWideChar(932, 0, sift_jis, -1, &wstr[0], wlen);

	//変換に必要なバイナリサイズの計測
	int slen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	//  なければ空白で返す
	if (slen == NULL) return "";

	//結果保管用
	std::string result(slen, 0);
	//Shift-Jisに
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], slen, NULL, NULL);

	return result.c_str(); // const char*化して返す

}
