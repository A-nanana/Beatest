//-----------------------------
// @name   background_node.cpp
// @brief  背景 クラス
// @auther A.namami
// @date   2026/3/12  新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "background_node.h"

void BackgroundNode::Update(float delta_time)
{
	scroll_pos_.Add(scroll_.x_, scroll_.y_);
	//位置ループ
	
	scroll_pos_.x_ = (int)scroll_pos_.x_ %(size_x_ );

	scroll_pos_.y_ = (int)scroll_pos_.y_ % (size_y_ );

}

void BackgroundNode::Draw(int screen_handle, Camera* camera)
{
	int draw_pos_y = world_position_.y_ - scroll_pos_.y_+ size_y_;
	int draw_pos_x = world_position_.x_ - scroll_pos_.x_ + size_x_;
	//位置毎に描画
	DrawGraph(draw_pos_x - size_x_ , draw_pos_y - size_y_ , graph_handle_, false);

	DrawGraph(draw_pos_x - size_x_, draw_pos_y, graph_handle_, false);
	DrawGraph(draw_pos_x, draw_pos_y - size_y_, graph_handle_, false);
	DrawGraph(draw_pos_x, draw_pos_y, graph_handle_, false);

}

void BackgroundNode::SetUp()
{
	GetGraphSize(graph_handle_, &size_x_, &size_y_);

}

BackgroundNode::BackgroundNode(const char* name, Vector2D scroll)
	:GraphNode(name,window_setting::null_param, window_setting::null_param)
{
	scroll_.Set(scroll);
	scroll_pos_.Set(window_setting::null_param, window_setting::null_param);
}
