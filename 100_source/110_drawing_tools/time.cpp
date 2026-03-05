//-----------------------------
// @name   time.cpp
// @brief  時間 クラスの実装部
// @auther A.namami
// @date   2026/2/19  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "DxLib.h"
#include "time.h"

Time::Time()
{
	old_time_ = GetNowCount();
	delta_ = 0.0f;
}

void Time::Update() {
	int now_time = GetNowCount();
	delta_ = now_time - old_time_;
	old_time_ = now_time;
}