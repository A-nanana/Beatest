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
GraphNode::GraphNode(const char* name, float x, float y)
{
	graph_handle_ = NULL;
	name_ = name;
	SetPosition(x, y);
	rotate_ = 0.0f;
	size_x_ = NULL;
	size_y_ = NULL;
}

GraphNode::GraphNode(const int graph_handle, float x, float y)
{
	graph_handle_ = graph_handle;
	name_ = "UseHandleOnly";
	SetPosition(x, y);
	rotate_ = 0.0f;
	size_x_ = NULL;
	size_y_ = NULL;
}

void GraphNode::SetName(const char* name)
{
	name_ = name;
}

//ロード
void GraphNode::Load()
{
	//既にあるか判定
	if (graph_handle_ != NULL) {
		//メモリ解放のため削除
		DeleteGraph(graph_handle_);
	}

	 graph_handle_ = LoadGraph(name_.c_str());
	 GetGraphSize(graph_handle_, &size_x_, &size_y_);

}

//リリース
void GraphNode::Release()
{
	DeleteGraph(graph_handle_);
}
//描画
void GraphNode::Draw(int screen_handle,Camera* camera)
{
	//カメラ内か
	if (camera->IsDraw(GetWorldPosition(),size_x_,size_y_)) {
		Vector2D draw_pos_(world_position_);
		draw_pos_.x_ += -camera->position_.x_ + size_x_ / 2;
		draw_pos_.y_ += -camera->position_.y_ + size_y_ / 2;
		DrawRotaGraph2(draw_pos_.x_, draw_pos_.y_,size_x_/2,size_y_/2, window_setting::graph_extender_* 0.5f
			,rotate_,graph_handle_, TRUE);
	}
}

