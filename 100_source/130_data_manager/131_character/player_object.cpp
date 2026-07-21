//-----------------------------
// @name   player_object.cpp
// @brief  プレイヤーオブジェクト クラス
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include <iostream>
#include "player_object.h"
#include "../../110_drawing_tools/line_node.h"
#include "../../110_drawing_tools/inputer.h"
#include "../../110_drawing_tools/defining.h"
#include "../../110_drawing_tools/tool.h"
#include "../134_other/window_manager.h"
#include "../../150_effect/151_player/player_effect.h"


PlayerObject* PlayerObject::player_ = nullptr;
PlayerObject::PlayerObject():ObjectCommon(file_set::player, WindowManager::GetInstance()->GetWindowCenterX(), WindowManager::GetInstance()->GetWindowCenterY(),window_setting::player_extender_,system_set::player_hit_size_x, system_set::player_hit_size_y)
{
	effect_ = new PlayerEffect(this);
	AddChild(effect_);
}

PlayerObject* PlayerObject::GetInstance()
{
	if (player_ == nullptr) {
		player_ = new PlayerObject();

	}
	return player_;
}


void PlayerObject::SetUp()
{
	//位置決定
	ObjectCommon::SetWorldPosition();
	
}

void PlayerObject::Update(float delta_time)
{

	//加算用
	Vector2D move_vector(window_setting::null_param,window_setting::null_param);
	
	//直前位置の記憶
	last_pos_.Set(world_position_);
	//スティックの取得
	{
		float add_x = 0.0f, add_y = 0.0f;
		Inputer::GetInstance()->GetNowStickAmount(&add_x, &add_y, 600);
		move_vector.Add(add_x, add_y);
	}
	//スティック量がとれないならボタンで計測
	if (move_vector.Length_2zyou() == 0) {

		//Wキー/Upで上に
		if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_W) || Inputer::GetInstance()->GetHitPad(PAD_INPUT_UP)) {
			move_vector.Add(window_setting::null_param, -system_set::player_walk_speed);
		}
		//Sキー/Downで下に
		if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_S) || Inputer::GetInstance()->GetHitPad(PAD_INPUT_DOWN)) {
			move_vector.Add(window_setting::null_param, system_set::player_walk_speed);
		}
		//Aキー/Leftで左に
		if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_A)|| Inputer::GetInstance()->GetHitPad(PAD_INPUT_LEFT)) {
			move_vector.Add(-system_set::player_walk_speed, window_setting::null_param);
		}
		//Dキー/Rightで右に
		if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_D) || Inputer::GetInstance()->GetHitPad(PAD_INPUT_RIGHT)) {
			move_vector.Add(system_set::player_walk_speed, window_setting::null_param);
		}
		//ノルム化
		move_vector.Normalize();
	}
	
	move_vector.Scale(system_set::player_walk_speed);
	
	//端の場合はクランプ
	CrampDouble(move_vector.x_, -last_pos_.x_, window_setting::size_x - size_x_ - last_pos_.x_);
	CrampDouble(move_vector.y_, -last_pos_.y_, window_setting::size_y -size_y_ - last_pos_.y_);
	
	//位置の加算
	SetPosition(position_.x_ + move_vector.x_, position_.y_ + move_vector.y_);
	ObjectCommon::SetWorldPosition();
	
	//エフェクト作成
	effect_->Create(is_effect_);

}



