//-----------------------------
// @name   background_node.h
// @brief  背景 クラス
// @auther A.namami
// @date   2026/3/12  新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __BACKGROUND_NODE_H__
#define __BACKGROUND_NODE_H__

#include "..\110_drawing_tools\graph_node.h"
#include "..\110_drawing_tools\Vector2.h"
#include "..\110_drawing_tools\defining.h"


class BackgroundNode:public GraphNode
{
protected:
	Vector2D scroll_;//スクロール速度
	Vector2D scroll_pos_;//スクロールの位置
	
	//更新(更新するときの時間)
	void Update(float delta_time) override;
	//描画(描画先)
	void Draw(int screen_handle, Camera* camera) override;

public:
	//コンストラクタ
	BackgroundNode(const char* name, Vector2D scroll);
};

#endif // !__BACKGROUND_NODE_H__
