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
#include <vector>
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

//-----------------------------
// @name   Controller
// @brief  コントローラー入力
// @memo   Dxライブラリ準拠
//------------------------------
class Controller {
public:
	int in_key_;//状態
	int x_, y_;//スティック状態

//コンストラクタ
	Controller() :in_key_(0),  x_(0), y_(0) {};

};
/*
ロジクールのキー

PAD_INPUT_DOWN  下矢印
PAD_INPUT_UP     上矢印
	多分左右も同じ
PAD_INPUT_1　A
PAD_INPUT_2　B
PAD_INPUT_3  X
PAD_INPUT_4　Y
PAD_INPUT_5　LB
PAD_INPUT_6　RB
PAD_INPUT_7　Back
PAD_INPUT_8　Start
PAD_INPUT_9　左スティック押し
PAD_INPUT_10	右スティック押し
PAD_INPUT_11　
*/

class Inputer
{

	static Inputer* instance_;//既にこれがあるか
	static const int kKeyInputAll = 256;//確認するキーの数
	
	Controller last_pad_;//直前のコントローラーの入力状態
	Controller now_pad_;//今のコントローラーの入力状態
	char key_buf_[kKeyInputAll]; //入力キーの状態を得る
	char key_buf_last_[kKeyInputAll]; //直前の入力キーの状態を得る

	Mouse now_;//今のマウス状態
	Mouse last_;//直前のマウス状態
	int mouse_wheel_;//マウスホイールの回転量

	int tag_;//取得したタグ
	bool is_use_controller_;//コントローラー使用有無

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

	//スティック入力量(単位変換つき)
	void GetStickAmount(float* x, float* y, const int per_param = 1000);
	//対象のボタンの投下状態
	bool GetHitPad(int key) { return ((now_pad_.in_key_ & key)!= 0); };
	//対象のボタンが押された
	bool GetDownPad(int key) { return (((now_pad_.in_key_ & key )!= 0) && ((last_pad_.in_key_ & key) == 0)); };
	//対象のボタンが離された
	bool GetUpPad(int key) { return (((now_pad_.in_key_ & key) == 0) && ((last_pad_.in_key_ & key) != 0)); };


	//セットされたタグ
	int GetTagParam() { return tag_; };
	//入力キーの状態を返す
	char* GetKeyState() {return key_buf_;};
	//コントローラーの有無
	bool GetIsPad() { return is_use_controller_; };

//  更新処理
	void Update();



};

