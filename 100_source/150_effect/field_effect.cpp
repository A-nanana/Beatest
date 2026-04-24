//-----------------------------
// @name   field_effect.cpp
// @brief  舞台エフェクト管理 クラス
// @auther A.namami
// @date   2026/3/12  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "field_effect.h"
#include "../110_drawing_tools/circle_node.h"
#include "../110_drawing_tools/defining.h"
#include "../130_data_manager/133_music/music_manager.h"
#include "../130_data_manager/134_other/window_manager.h"

//------------------------------
// @name   BackBeatEffect
// @brief  背景ラインエフェクト
// @memo   
//------------------------------

void BackBeatEffect::Update(float delta_time)
{
	//時間追加
	time_count_ += delta_time;

	//時間がカウント更新時間になったら大きさリセット
	if (time_count_ >= time_per_loop_) {
		
		time_count_ = 0.0f;
	}

	//  子の分繰り返し
	for (Node* child : children_) {
		//キャスト
		CircleNode* eff_line = dynamic_cast<CircleNode*>(child);
		//対象か
		if (eff_line != nullptr) {
			eff_line->SetSize( max_size_* time_count_/(time_per_loop_/beat_time_));
		}
	}
}



BackBeatEffect::BackBeatEffect(int time_per_loop, int beat_time,Vector2D vector_point)
	:AlphaNode(effect_param::back_alpha)
{
	SetPosition(vector_point);
	time_per_loop_ = time_per_loop;
	max_size_ = WindowManager::GetInstance()->GetWindowLength();
	beat_time_ = beat_time;
	time_count_ = 0.0f;

	AddChild(new CircleNode(position_, window_setting::null_param, false, GetColor(255, 255, 255), effect_param::back_thick));
}

//------------------------------
// @name   FieldEffect
// @brief  背景のエフェクト管理 
// @memo   
//------------------------------
FieldEffect::FieldEffect()
{
	AddChild(new BackBeatEffect((float)(MusicManager::GetInstance()->GetMsPerHyousi()* MusicManager::GetInstance()->GetMusicData().hyousi_), MusicManager::GetInstance()->GetMusicData().hyousi_,
		{ window_setting::null_param,window_setting::null_param }));
}
