//-----------------------------
// @name   line_node.h
// @brief  線ノード クラスの宣言部
// @auther A.namami
// @date   2026/3/11  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "line_node.h"
#include "camera.h"
#include "tool.h"

//-----------------------------
// @name   LineNode
// @brief  線ノード
// @memo   セットしてから使うこと
//------------------------------
LineNode::LineNode(float x, float y, float last_pos_x, float last_pos_y, int color_code, float thick)
{
	SetPosition(x, y);
	length_.Set(last_pos_x, last_pos_y);
	color_code_ = color_code;
	thick_ = thick;
}

//ロード
void LineNode::Load() {

}
//リソース解放
void LineNode::Release() {

}
//更新(更新するときの時間)
void LineNode::Update(float delta_time) {

}
//描画(描画先)
void LineNode::Draw(int screen_handle, Camera* camera) {
	DrawLineAA(world_position_.x_,world_position_.y_,length_.x_,length_.y_,color_code_,thick_);
}

//-----------------------------
// @name   LineEffect
// @brief  線エフェクト
// @memo   セットしてから使うこと
//------------------------------
LineEffect::LineEffect(float x, float y, float last_pos_x, float last_pos_y, int color_code, float thick, int looper, float time)
	:AlphaNode(NULL)
{
	SetPosition(x, y);
	length_.Set(last_pos_x, last_pos_y);
	color_code_ = color_code;
	thick_ = thick;

	looper_max_ = looper;
	looper_count_ = 0;
	time_per_loop_harf_ = time / 2;
	time_count_ = 0;
}


void LineEffect::Update(float delta_time)
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


	//アルファ値追加
	//対象があるか

	//奇数か偶数かで処理切り替え
	if ((looper_count_ % 2) == 0) {
		Add((float)(delta_time / time_per_loop_harf_));
	}
	else {
		Sub((float)(delta_time / time_per_loop_harf_));

	}

}

void LineEffect::Draw(int screen_handle, Camera* camera)
{

	AlphaNode::Draw(screen_handle, camera);
	DrawLineAA(world_position_.x_, world_position_.y_, length_.x_, length_.y_, color_code_, thick_);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NULL);

}


