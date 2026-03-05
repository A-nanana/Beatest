//-----------------------------
// @name   time.h
// @brief  時間 クラスの宣言部
// @auther A.namami
// @date   2026/2/19  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once
class Time
{
	int old_time_;//少し前の時間
	float delta_;//現在時間との差

public:
//  コンストラクタ
	Time();

//  更新
	void Update();
//  ゲッター
	float GetDelta() { return delta_; };
};

