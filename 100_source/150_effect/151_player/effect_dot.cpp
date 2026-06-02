//-----------------------------
// @name   effect_dot.cpp
// @brief  プレイヤーエフェクト 素材 クラス
// @auther A.namami
// @date   2026/6/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "effect_dot.h"
#include "../../110_drawing_tools/defining.h"

EffectDot::EffectDot(float rotate, int speed, Vector2D pos, Vector2D size, unsigned int color, float thick, bool is_full)
	:BoxNode(pos,size,color,thick,is_full),rotate_(rotate),it_speed_(speed)
{
}

void EffectDot::Update(float delta_time)
{
	Vector2D speed_; //速度

	// 角度込みで計算
	speed_.x_ = cosf(rotate_) * it_speed_;
	speed_.y_ = sin(rotate_) * it_speed_;



	// 位置更新
	SetPosition(position_.x_ + speed_.x_, position_.y_ + speed_.y_);
	SetWorldPosition();
}
