//-----------------------------
// @name   window_manager.h
// @brief  ウィンドウ管理 クラス
// @auther A.namami
// @date   2026/4/24  新規作成
// @memo   エラー型が来た場合は-1で返します
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include "../../110_drawing_tools/Vector2.h"
#include "../../110_drawing_tools/defining.h"

class WindowManager
{
	static WindowManager* instance_;//実体
	Vector2D window_size_;//ウィンドウの大きさ
	float window_lemgth_;//ウィンドウ端までの長さ
	int color_bit_;//カラービット
	//  コンストラクタ
	WindowManager();
	//  デストラクタ
	~WindowManager() {};
public:
	//  複製防止
	WindowManager operator= (const WindowManager&) = delete;
	WindowManager& operator= (WindowManager&) = delete;

	//  インスタンスアクセス
	static WindowManager* GetInstance();
	//  ウィンドウの初期設定を一括でする関数
	void WindowSettings();
	//  ゲッター
	Vector2D GetWindowSize() { return window_size_; };//ウィンドウの大きさ
	Vector2D GetSelecterCenter() {
		return { (window_size_.x_ / line_set::amount_x_max) + line_set::selecter_pos_x,
		(window_size_.y_ / line_set::amount_y_max) + line_set::selecter_pos_y };};//セレクターの初期位置
	Vector2D GetPopUpSize() { return {window_size_.x_ * window_setting::pop_up_extend_x,
		window_size_.y_ * window_setting::pop_up_extend_y }; };//ポップアップの大きさ
	float GetWindowCenterX() { return window_size_.x_ / 2; };//中央位置x
	float GetWindowCenterY() { return window_size_.y_ / 2; };//中央位置y
	float GetWindowLength() { return window_lemgth_; };//対角線の長さ
};
#endif // !__WINDOW_MANAGER_H__
