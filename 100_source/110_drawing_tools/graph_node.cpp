//-----------------------------
// @name   graph_node.cpp
// @brief  画像ノード クラスの実装部
// @auther A.namami
// @date   2026/2/16  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "graph_node.h"
#include "tool.h"
#include "camera.h"
#include "defining.h"
#include "../140_roading_from_other/graph_roader.h"

GraphNode::GraphNode(const char* name, float x, float y)
{
	graph_handle_ = NULL;
	name_ = new std::string(name);
	SetPosition(x, y);
	rotate_ = 0.0f;
	size_x_ = NULL;
	size_y_ = NULL;
}

GraphNode::GraphNode(const int graph_handle, float x, float y)
{
	graph_handle_ = graph_handle;
	name_ = nullptr;
	SetPosition(x, y);
	rotate_ = 0.0f;
	size_x_ = NULL;
	size_y_ = NULL;
}

void GraphNode::SetName(const char* name)
{
	//既にあるなら破棄
	if (name_ != nullptr) {
		delete name_;
	}

	name_ = new std::string(name);
}

//ロード
void GraphNode::Load()
{
	//画像読み込みが必要か
	if(name_ )
	 graph_handle_ = GraphRoader::GetInstance()->RoadingGraph(name_->c_str());
	//既にサイズが設定されているか
	 if (size_x_ > NULL && size_y_ > NULL) {
		 return;
	}
	 GetGraphSize(graph_handle_, &size_x_, &size_y_);
	 size_x_ *= window_setting::graph_extender_;
	 size_y_ *= window_setting::graph_extender_;
}

//リリース
void GraphNode::Release()
{
	
}
//描画
void GraphNode::Draw(int screen_handle,Camera* camera)
{
	//カメラ内か
	if (camera->IsDraw(GetWorldPosition(),size_x_,size_y_)) {
		Vector2D draw_pos_;
		draw_pos_.x_ = camera->DrawPositionX(world_position_.x_) + size_x_ / 2;
		draw_pos_.y_ = camera->DrawPositionY(world_position_.y_) + size_y_ / 2;
		DrawRotaGraph(draw_pos_.x_, draw_pos_.y_, window_setting::graph_extender_
			,rotate_,graph_handle_, TRUE);
	}
}

void GraphNode::Draw(int screen_handle) {
	DrawRotaGraph(world_position_.x_ + size_x_ / 2, world_position_.y_ + size_y_ / 2, window_setting::graph_extender_
		, rotate_, graph_handle_, TRUE);
}

int GraphNode::GetSizeX()
{
	return size_x_;
}

int GraphNode::GetSizeY()
{
	return size_y_;
}

