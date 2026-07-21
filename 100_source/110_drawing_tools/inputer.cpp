//-----------------------------
// @name   inputer.cpp
// @brief  入力 クラスの実装部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "inputer.h"


Inputer* Inputer::instance_ = nullptr;//既にこれがあるか

Inputer::Inputer()
{
	for (int i = 0; i < kKeyInputAll; i++) {
		key_buf_last_[i] = key_buf_[i] = 0;
	}
	mouse_wheel_ = 0;
	tag_ = 0;
}

Inputer::~Inputer()
{
}

Inputer* Inputer::GetInstance()
{

	if (instance_ == nullptr) {
		instance_ = new Inputer();
	}
	return instance_;
}

void Inputer::GetMousePointer(int* x, int* y)
{
	*x = now_.x_;
	*y = now_.y_;
}

void Inputer::GetStickAmount(float* x, float* y, const int per_param)
{
	if (now_pad_.x_ != 0) {
		*x = (now_pad_.x_ - last_pad_.x_) / per_param;
	}
	else {
		*x = (now_pad_.x_) / per_param;
	}
	if (now_pad_.y_ != 0) {
		*y = (now_pad_.y_ - last_pad_.y_) / per_param;
	}
	else {
		*y = (now_pad_.y_) / per_param;
	}
}

void Inputer::GetNowStickAmount(float* x, float* y, const int per_param)
{
	*x = now_pad_.x_ / per_param;
	*y = now_pad_.y_ / per_param;
}

void Inputer::Update()
{
	//マウスの入力状態更新
	last_ = now_;
	//押し離しの情報はあるか
	if (GetMouseInputLog2(&now_.bottom_, &now_.x_, &now_.y_, &now_.log_type_) == -1) {
		GetMousePoint(&now_.x_, &now_.y_);

	}
	mouse_wheel_ = GetMouseWheelRotVol();
	

	//キーの入力状態更新
	for (int i = 0; i < kKeyInputAll; i++) {
		key_buf_last_[i] = key_buf_[i];
	}
	GetHitKeyStateAll(key_buf_);

	//パッドの接続取得
	if (GetJoypadNum()) {
		is_use_controller_ = true;
	}
	else {
		is_use_controller_ = false;
	}

	//パッド更新
	last_pad_ = now_pad_;
	now_pad_.in_key_ = GetJoypadInputState(DX_INPUT_PAD1);
	GetJoypadAnalogInput(&now_pad_.x_, &now_pad_.y_, DX_INPUT_PAD1);
}
