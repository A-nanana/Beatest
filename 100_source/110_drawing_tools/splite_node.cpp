//-----------------------------
// @name   splite_node.cpp
// @brief  スプライトノード クラス
// @auther A.namami
// @date   2026/3/11  新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "DxLib.h"
#include "splite_node.h"

//ロード
void SpliteNode::Load() {
	//最大数特定用　画像サイズ
	int x, y;

	graph_handle_ = LoadGraph(name_.c_str());
	GetGraphSize(graph_handle_, &x, &y);

	pos_num_.Set(x / separate_size_.x_, y / separate_size_.y_);
	all_indix_ = pos_num_.x_ * pos_num_.y_;
}
//リソース解放
void SpliteNode::Release() {

	DeleteGraph(graph_handle_);
}
//更新(更新するときの時間)
void SpliteNode::Update(float delta_time) {
	time_count_ += delta_time;

	//ループさせる
	now_index_ = (time_count_ / step_time_ms) % all_indix_;


}
//描画(描画先)
void SpliteNode::Draw(int screen_handle) {
	DrawRectGraph(world_position_.x_, world_position_.y_,
		separate_size_.x_ * (now_index_ % (int)(pos_num_.x_)), separate_size_.y_ * (now_index_ / (int)(pos_num_.x_)), separate_size_.x_, separate_size_.y_,
		graph_handle_, TRUE);
}

SpliteNode::SpliteNode(const char* name)
{
	name_ = name;
	graph_handle_ = NULL;
	all_indix_ = 0;//最大タイル数
	now_index_ = 0;//今のタイル番号

	time_count_ = 0;//変換用カウンタ
	is_loop_ = false;//ループの有無
}

SpliteNode::SpliteNode(const char* name, Vector2D pos)
{
	SetPosition(pos);
	name_ = name;
	graph_handle_ = NULL;
	all_indix_ = 0;//最大タイル数
	now_index_ = 0;//今のタイル番号

	time_count_ = 0;//変換用カウンタ
	is_loop_ = false;//ループの有無
}

SpliteNode::SpliteNode(const char* name, Vector2D pos, Vector2D separate_size,bool is_loop)
{
	SetPosition(pos);
	name_ = name;
	graph_handle_ = NULL;
	all_indix_ = 0;//最大タイル数
	now_index_ = 0;//今のタイル番号

	time_count_ = 0;//変換用カウンタ
	is_loop_ = is_loop;//ループの有無
	separate_size_.Set(separate_size);
}
