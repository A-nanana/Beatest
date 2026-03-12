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
	scroll_pos_.x_ = (int)(scroll_pos_.x_ + size_x_) % size_x_;
	scroll_pos_.y_ = (int)(scroll_pos_.y_ + size_y_) % size_y_;
}

void BackgroundNode::Draw(int screen_handle, Camera* camera)
{
	//位置毎に描画
	DrawRectGraph(world_position_.x_, world_position_.y_, scroll_pos_.x_, scroll_pos_.y_, size_x_ -scroll_pos_.x_, size_y_ - scroll_pos_.y_, graph_handle_, true);
	
	DrawRectGraph(world_position_.x_ +size_x_- scroll_pos_.x_, world_position_.y_ , window_setting::null_param, scroll_pos_.y_, scroll_pos_.x_,size_y_- scroll_pos_.y_, graph_handle_, true);
	
	DrawRectGraph(world_position_.x_ , world_position_.y_ + size_y_ - scroll_pos_.y_, scroll_pos_.x_, window_setting::null_param, size_x_ - scroll_pos_.x_,  scroll_pos_.y_, graph_handle_, true);

	DrawRectGraph(world_position_.x_ + size_x_ - scroll_pos_.x_, world_position_.y_ + size_y_ - scroll_pos_.y_, scroll_pos_.x_, scroll_pos_.y_, size_x_ - scroll_pos_.x_, size_y_ - scroll_pos_.y_, graph_handle_, true);

}

BackgroundNode::BackgroundNode(const char* name, Vector2D scroll)
	:GraphNode(name,window_setting::null_param, window_setting::null_param)
{
	scroll_.Set(scroll);
	scroll_pos_.Set(window_setting::null_param, window_setting::null_param);
}
