//-----------------------------
// @name   window_manager.cpp
// @brief  ウィンドウ管理 クラス
// @auther A.namami
// @date   2026/4/24  新規作成
// @memo   エラー型が来た場合は-1で返します
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "window_manager.h"

#include <math.h> //数学ライブラリ
#include "DxLib.h"

WindowManager* WindowManager::instance_ = nullptr;

//コンストラクタ
WindowManager::WindowManager() {
	window_size_.Set( window_setting::size_x, window_setting::size_y );
	color_bit_ = window_setting::color_bit;
	window_lemgth_ = sqrtf(window_size_.x_ * window_size_.x_ + window_size_.y_ * window_size_.y_);
}

WindowManager* WindowManager::GetInstance() {
	if (instance_ == nullptr) {
		instance_ = new WindowManager();
	}
	return instance_;
}

void WindowManager::WindowSettings()
{
	//ウィンドウ自体の設定
	ChangeWindowMode(TRUE);
	//ウィンドウのモード設定
	SetGraphMode(window_size_.x_, window_size_.y_, color_bit_);

	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetUsePremulAlphaConvertLoad(TRUE);

}