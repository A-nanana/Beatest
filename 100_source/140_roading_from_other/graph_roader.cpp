//-----------------------------
// @name   graph_roader.cpp
// @brief  画像読み込み クラス
// @auther A.namami
// @date   2026/4/20  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "graph_roader.h"
#include "DxLib.h"

GraphRoader* GraphRoader::roader_ = nullptr;
GraphRoader::GraphRoader()
{

}

GraphRoader::~GraphRoader()
{
	//残っている画像の削除
	for (auto graph_handle : graph_) {
		DeleteGraph(graph_handle.second);
		graph_.erase(graph_handle.first);
	}
}

GraphRoader* GraphRoader::GetInstance() {
	//インスタンスの有無
	if (roader_ == nullptr) {
		roader_ = new GraphRoader();
	}
	return roader_;
};

int GraphRoader::RoadingGraph(std::string& name)
{
	//存在の有無の確認
	if (graph_.find(name) == graph_.end()) {
		//読み込む
		graph_.insert({ name,LoadGraph(name.c_str()) });
	}
	return graph_[name];
}

void GraphRoader::DeletingGraph(std::string& name)
{
	//存在の有無の確認
	if (graph_.find(name) != graph_.end()) {
		DeleteGraph(graph_[name]);
		graph_.erase(name);
	}
}
