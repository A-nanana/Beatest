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
#include "effect_dot.h"
#include "../../130_data_manager/131_character/player_object.h"
#include "../../130_data_manager/133_music/music_manager.h"
#include "../../130_data_manager/134_other/color_manager.h"
#include "../../110_drawing_tools/alpha_node.h"
#include "../../110_drawing_tools/box_node.h"
#include "../../110_drawing_tools/defining.h"


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

HitLineEffect::HitLineEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size, int red,int green, int blue, int type)
	:AlphaNode(window_setting::null_param)
{
	SetWorldPosition();
	looper_max_ = loop_max;
	looper_count_ = 0;
	time_count_ = 0.0f;
	time_per_loop_harf_ = time_per_loop / 2;
	eff_type_ = type;
	
	color_code_ = GetColor(red, green, blue);
	SetEffPositon(vector_point, size);

}

HitLineEffect::HitLineEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size, int color_code, int type)
	:AlphaNode(window_setting::null_param) 
{
	SetWorldPosition();
	looper_max_ = loop_max;
	looper_count_ = 0;
	time_count_ = 0.0f;
	time_per_loop_harf_ = time_per_loop / 2;
	eff_type_ = type;

	color_code_ = color_code;
	SetEffPositon(vector_point, size);
}


void HitLineEffect::SetEffPositon(Vector2D player_point, Vector2D graph_size)
{
	//初期位置
	Vector2D first_pos(player_point.x_ - graph_size.x_ / 2, player_point.y_ - graph_size.y_ / 2);
	first_pos.Sub(world_position_);
	//四角を描画
	AddChild(new BoxNode({ first_pos.x_, first_pos.y_ }, { graph_size.x_, graph_size.y_ },color_code_, effect_param::eff_thick));
}


//------------------------------
// @name   HitDotEffect
// @brief  点ヒットエフェクト
// @memo   
//------------------------------

void HitDotEffect::Update(float delta_time)
{
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


	//  子の分繰り返し
	for (Node* child : children_) {
		//キャスト
		BoxNode* eff_line = dynamic_cast<BoxNode*>(child);
		//対象か
		if (eff_line != nullptr) {
			eff_line->SubSize({ effect_param::pos_out_x,effect_param::pos_out_y });
		}
	}

}

HitDotEffect::HitDotEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size, int red, int green, int blue, int type)
	:AlphaNode(window_setting::null_param)
{
	SetWorldPosition();
	looper_max_ = loop_max;
	looper_count_ = 0;
	time_count_ = 0.0f;
	time_per_loop_harf_ = time_per_loop / 2;
	eff_type_ = type;

	color_code_ = GetColor(red, green, blue);
	SetEffPositon(vector_point, size);

}

HitDotEffect::HitDotEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size, int color_code, int type)
	:AlphaNode(window_setting::null_param)
{
	SetWorldPosition();
	looper_max_ = loop_max;
	looper_count_ = 0;
	time_count_ = 0.0f;
	time_per_loop_harf_ = time_per_loop / 2;
	eff_type_ = type;

	color_code_ = color_code;
	SetEffPositon(vector_point, size);
}

void HitDotEffect::SetEffPositon(Vector2D player_point, Vector2D graph_size)
{
	//初期位置
	Vector2D first_pos(player_point.x_ - graph_size.x_ / 2, player_point.y_ - graph_size.y_ / 2);
	first_pos.Sub(world_position_);
	//角度分割
	for (int i = 0; i < effect_param::dec_per_dot; i++) {
		//四角を描画
		AddChild(new EffectDot((M_PI * 2 * i) / effect_param::dec_per_dot, effect_param::max_per_length , { first_pos.x_, first_pos.y_ }, { graph_size.x_, graph_size.y_ }, color_code_, effect_param::eff_thick));
	}
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
				//存在フラグを倒す
				flg_ &= ~eff_line->GetFlg();
				player_->RestEffect(eff_line->GetFlg());
				DeleteChild(eff_line);
				
			}
			continue;
		}
		//キャスト
		HitDotEffect* eff_dot = dynamic_cast<HitDotEffect*>(child);
		//対象か
		if (eff_dot != nullptr) {
			//終了しているか
			if (eff_dot->IsEnd()) {
				//存在フラグを倒す
				flg_ &= ~eff_dot->GetFlg();
				player_->RestEffect(eff_dot->GetFlg());
				DeleteChild(eff_dot);

			}
		}
	}
}

PlayerEffect::PlayerEffect(PlayerObject* player)
{
	flg_ = NULL;
	player_ = player;
}

void PlayerEffect::Create(int flg)
{
	

	//フラグで各種切り替え
	//クリティカル判定 & 画面上にエフェクトがない
	if ((flg & effect_set::effect_critical) & ~(flg_ & effect_set::effect_critical)) {
		
		AddChild(new HitLineEffect(effect_param::loop_hit, effect_param::time_per_loop, player_->GetCenter(), player_->GetSize(),
			ColorManager::GetInstance()->SerchColor(string_set::font_eff1) , effect_set::effect_critical));
		//Se再生
		MusicManager::GetInstance()->PlaySe(k_play_critical);
	}
	
	//回避判定 & 画面上にエフェクトがない
	if ((flg & effect_set::effect_avoid) & ~(flg_ & effect_set::effect_avoid)) {
		
		AddChild(new HitLineEffect(effect_param::loop_hit, effect_param::time_per_loop, player_->GetCenter(), player_->GetSize(),
			ColorManager::GetInstance()->SerchColor(string_set::font_eff2), effect_set::effect_avoid));
		
	}

	//当たり判定 & 画面上にエフェクトがない
	if ((flg & effect_set::effect_hit) & ~(flg_ & effect_set::effect_hit)) {
		AddChild(new HitDotEffect(effect_param::loop_hit, effect_param::time_per_loop, player_->GetCenter(), player_->GetSize(),
			ColorManager::GetInstance()->SerchColor(string_set::font_eff2), effect_set::effect_hit));

	}

	//通常判定 & 画面上にエフェクトがない
	if ((flg & effect_set::effect_none) & ~(flg_ & effect_set::effect_none)) {
	
	}
	//フラグを立てる
	flg_ |= flg;
}
