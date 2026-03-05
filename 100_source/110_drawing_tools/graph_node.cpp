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
GraphNode::GraphNode(const char* name, float x, float y)
{
	graph_handle_ = NULL;
	name_ = name;
	SetPosition(x, y);

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
	if (camera->IsDraw(GetWorldPosition())) {
		DrawGraph(Abs(world_position_.x_ - camera->position_.x_), Abs(world_position_.y_ - camera->position_.y_), graph_handle_, false);
	}
}

