//-----------------------------
// @name   box_node.h
// @brief  箱ノード クラスの宣言部
// @auther A.namami
// @date   2026/3/12  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once

#include "node.h"
#include "Vector2.h"
class BoxNode :public Node
{
protected:
	Vector2D size_; //大きさ
	bool is_full_;//中を埋めるか
	unsigned int color_code_;//色コード
	float thick_;//太さ

	//ロード
	void Load() {};
	//リソース解放
	void Release() {};
	//更新(更新するときの時間)
	void Update(float delta_time) {};
	//描画(描画先)
	void Draw(int screen_handle,Camera* camera) override;
public:
	//コンストラクタ
	BoxNode(Vector2D pos, Vector2D size, unsigned int color,float thick,bool is_full = false);
	//サイズ変化
	void AddSize(Vector2D add);//加算(中心変化なし)
	void SubSize(Vector2D sub);//減算
};

