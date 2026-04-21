//-----------------------------
// @name   defining.cpp
// @brief  数を定義する場所
// @auther A.namami
// @date   2026/2/26 新規作成
// @memo   TFはDXライブラリ準拠です
//         項目ごとに名前空間で分けてます
// 
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "defining.h"

#include <math.h> //数学ライブラリ

#include "DxLib.h"
#include "Vector2.h"

//-----------------------------
// @name   window_setting
// @brief  ウィンドウ関係
// @memo   
//------------------------------
void window_setting::WindowSettings()
{
	//ウィンドウ自体の設定
	ChangeWindowMode(TRUE);
	//ウィンドウのモード設定
	SetGraphMode(size_x, size_y,color_bit);

	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetUsePremulAlphaConvertLoad(TRUE);
	
	
}
