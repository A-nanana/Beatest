//-----------------------------
// @name   inputer.h
// @brief  入力 クラスの宣言部
// @auther A.namami
// @date   2026/2/18  新規作成
//		   2026/2/26 Tag取得関係を追加(ラベリングできるようにしたかった)
// 
// @memo   エラー型が来た場合は-1で返します
//         Dxライブラリ準拠
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once
#include "DxLib.h"


//-----------------------------
// @name   Mouse
// @brief  マウス入力
// @memo   Dxライブラリ準拠
//------------------------------
class Mouse{
public:
	int x_,y_;//マウスの位置
	int bottom_;// マウスボタンの情報
	int log_type_;//クリックログの形態

//  コンストラクタ
	Mouse() :x_(0), y_(0), bottom_(0), log_type_(0) {};
};


class Inputer
{
	static Inputer* instance_;//既にこれがあるか
	static const int kKeyInputAll = 256;//確認するキーの数
	char key_buf_[kKeyInputAll]; //入力キーの状態を得る
	char key_buf_last_[kKeyInputAll]; //直前の入力キーの状態を得る

	Mouse now_;//今のマウス状態
	Mouse last_;//直前のマウス状態
	int mouse_wheel_;//マウスホイールの回転量

	int tag_;//取得したタグ

protected:

	//  コンストラクタ
	Inputer();

	//  デストラクタ
	~Inputer();


public:
//  取得
	static Inputer* GetInstance();

//  セッター
	void SetGettingTag(int tag) { tag_ = tag; };

	//  ゲッター
	//対象のキーの投下状態
	bool GetHitKey(int key) { return (key_buf_[key] == 1); };
	//対象のキーが押された
	bool GetDownKey(int key) { return (key_buf_[key] == 1) && (key_buf_last_[key] == 0); };
	//対象のキーが離された
	bool GetUpKey(int key) { return (key_buf_[key] == 0) && (key_buf_last_[key] == 1); };

	//ポインタの位置
	void GetMousePointer(int* x, int* y);
	//対象のマウスの投下状態
	bool GetHitMouse(int key) { return ((now_.bottom_ & key) != 0) && (now_.log_type_ == MOUSE_INPUT_LOG_DOWN); };
	//対象のマウスが押された
	bool GetDownMouse(int key) { return (now_.log_type_ == MOUSE_INPUT_LOG_DOWN) && (last_.log_type_ == MOUSE_INPUT_LOG_UP) && ((now_.bottom_ & key) != 0); };
	//対象のマウスが離された
	bool GetUpMouse(int key) { return ((now_.bottom_ & key) != 0) && (now_.log_type_ == MOUSE_INPUT_LOG_UP) && (last_.log_type_ == MOUSE_INPUT_LOG_DOWN); };
	//マウスの回転量
	int GetMouseWheel() { return mouse_wheel_; };

	//セットされたタグ
	int GetTagParam() { return tag_; };

//  更新処理
	void Update();



};

