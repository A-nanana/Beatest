//-----------------------------
// @name   chanks.h
// @brief  Wavデータ クラス
// @auther A.namami
// @date   2026/6/4  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "chanks.h"

Time::Time(int sec)
{
	ChangeTime(sec);
}

void Time::ChangeTime(int sec)
{
	hour_ = sec / (60 * 60);
	sec -= hour_ * 60 * 60;
	min_ = (sec / 60);
	sec -= min_ * 60;
	sec_ = sec;

}

int minInt(int a, int b)
{
	if (a < b) return a;
	else return b;
}
