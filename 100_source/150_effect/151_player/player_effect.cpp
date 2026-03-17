//-----------------------------
// @name   player_effect.cpp
// @brief  プレイヤーエフェクト クラス
// @auther A.namami
// @date   2026/3/11  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "player_effect.h"
#include "..\..\130_data_manager\131_character\player_object.h"
#include "..\..\130_data_manager\133_music\music_manager.h"
#include "..\..\110_drawing_tools\alpha_node.h"
#include "..\..\110_drawing_tools\box_node.h"
#include "..\..\110_drawing_tools\defining.h"


//------------------------------
// @name   HitLineEffect
// @brief  ラインヒットエフェクト
// @memo   
//------------------------------

//更新(更新するときの時間)
void HitLineEffect::Update(float delta_time) {
	//時間追加
	time_count_ += delta_time;


	//時間がカウント更新時間になったらループカウント追加
	if (time_count_ >= time_per_loop_harf_) {
		looper_count_++;
		time_count_ = 0.0f;
	}
	//必要ループ以上なら終わり
	if (looper_count_ > looper_max_) {
		return;
	}


	//奇数か偶数かで処理切り替え
	if ((looper_count_ % 2) == 0) {
		Add((float)(delta_time / time_per_loop_harf_));
	}
	else {
		Sub((float)(delta_time / time_per_loop_harf_));

	}

//  子の分繰り返し
	for (Node* child : children_) {
		//キャスト
		BoxNode* eff_line = dynamic_cast<BoxNode*>(child);
		//対象か
		if (eff_line != nullptr) {
			eff_line->AddSize({ effect_param::pos_out_x,effect_param::pos_out_y });
		}
	}
	
}

HitLineEffect::HitLineEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size)
	:AlphaNode(window_setting::null_param)
{
	SetWorldPosition();
	SetEffPositon(vector_point, size);
	looper_max_ = loop_max;
	looper_count_ = 0;
	time_count_ = 0.0f;
	time_per_loop_harf_ = time_per_loop / 2;
}

void HitLineEffect::SetEffPositon(Vector2D player_point, Vector2D graph_size)
{
	//初期位置
	Vector2D first_pos(player_point.x_ - graph_size.x_ / 2, player_point.y_ - graph_size.y_ / 2);
	first_pos.Sub(world_position_);
	//四角を描画
	//線でやるのは後で多角形にするときのため
	AddChild(new BoxNode({ first_pos.x_, first_pos.y_ }, { graph_size.x_, graph_size.y_ }, GetColor(255, 0, 255), effect_param::eff_thick));
	
}

//------------------------------
// @name   PlayerEffect
// @brief  プレイヤーのエフェクト管理 
// @memo   
//------------------------------
void PlayerEffect::SetUp() {
	SetPosition(NULL, NULL);

}

void PlayerEffect::Update(float delta_time) {
	//プレイヤーを確実に追従させたい
	SetWorldPosition(player_->GetCenter());
//  子の分繰り返し
	for (Node* child : children_) {
		//キャスト
		HitLineEffect* eff_line = dynamic_cast<HitLineEffect*>(child);
		//対象か
		if (eff_line != nullptr) {
			//終了しているか
			if (eff_line->IsEnd()) {
				DeleteChild(eff_line);
			}
		}
	}
}

PlayerEffect::PlayerEffect(PlayerObject* player)
{
	player_ = player;
}

void PlayerEffect::Create(int flg)
{
	//フラグで切り替え
	
	if ((flg & effect_set::effect_critical)) {
		AddChild(new HitLineEffect(effect_param::loop_hit, effect_param::time_per_loop, player_->GetCenter(), player_->GetSize()));
		//Se再生
		MusicManager::GetInstance()->PlaySe(k_play_critical);
		//エフェクトのフラグを消す
		player_->RestEffect(effect_set::effect_critical);
	}
	if ((flg & effect_set::effect_avoid)) {
		AddChild(new HitLineEffect(effect_param::loop_hit, effect_param::time_per_loop, player_->GetCenter(), player_->GetSize()));
		//エフェクトのフラグを消す
		player_->RestEffect(effect_set::effect_avoid);
	}
	if ((flg & effect_set::effect_none)) {
		//エフェクトのフラグを消す
		player_->RestEffect(effect_set::effect_none);
	}
}
