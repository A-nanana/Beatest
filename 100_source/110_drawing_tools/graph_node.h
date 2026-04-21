//-----------------------------
// @name   graph_node.h
// @brief  画像ノード クラスの宣言部
// @auther A.namami
// @date   2026/2/16  新規作成
//         2026/3/4  Cameraに対応
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

#include <string>
#include "node.h"
class GraphNode:public Node
{
protected:
	int graph_handle_; //画像ハンドル
	std::string name_; //画像名
	float rotate_; //回転
	int size_x_,size_y_;//大きさ

public:
//  コンストラクタ(x,yは相対位置)
	GraphNode(const char* name, float x,float y);
	GraphNode(const int graph_handle, float x, float y);

//  セッター
	void SetName(const char* name);//名前

//  オーバーライド系列
	//ロード
	void Load() override;
	//リリース
	void Release() override;
	//描画
	void Draw(int screen_handle, Camera* camera) override;
	void Draw(int screen_handle);

//  ゲッター
	int GetSizeX();//x
	int GetSizeY();//y

};

