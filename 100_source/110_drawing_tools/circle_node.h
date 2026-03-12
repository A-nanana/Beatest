//-----------------------------
// @name   circle_node.h
// @brief  円ノード クラスの宣言部
// @auther A.namami
// @date   2026/3/12  新規作成
// @memo   エラー型が来た場合は-1で返します
//         中に入れてあるやつはDxライブラリの初期値と対応
// 
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once

#include "node.h"
#include "Vector2.h"

class CircleNode:public Node
{
	float size_; //大きさ
	bool is_full_;//中を埋めるか
	unsigned int color_code_;//色コード
	float thick_;//太さ
	float angle_;//角度

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
	CircleNode(Vector2D pos, float r, bool is_full, unsigned int color, float thick = 1.0f,float angle = 0.0f);
	//サイズ変化
	void AddSize(float add) { size_ += add; };//加算(中心変化なし)
	void SubSize(float sub) { size_ -= sub; };//減算
	void SetSize(float r) { size_ = r; };//サイズ設定
};

