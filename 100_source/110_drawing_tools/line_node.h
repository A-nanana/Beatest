//-----------------------------
// @name   line_node.h
// @brief  線ノード クラスの宣言部
// @auther A.namami
// @date   2026/3/11  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once

#include "node.h"

class AlphaNode;
//-----------------------------
// @name   LineNode
// @brief  線ノード
// @memo   セットしてから使うこと
//------------------------------
class LineNode:public Node
{
protected:
	Vector2D position_2_; //最終位置
	unsigned int color_code_; //色コード
	float thick_;//太さ

//  各自でオーバーライドする
	//ロード
	void Load();
	//リソース解放
	void Release();
	//更新(更新するときの時間)
	void Update(float delta_time) override;
	//描画(描画先)
	void Draw(int screen_handle, Camera* camera) override;

public:
	//コンストラクタ(相対位置)
	LineNode(float x, float y, float last_pos_x, float last_pos_y,unsigned int color_code, float thick);
	//ノードセット
	void SetWorldPosition() override;

};

//-----------------------------
// @name   LineEffect
// @brief  線エフェクト
// @memo   セットしてから使うこと
//------------------------------
class LineEffect :public LineNode
{
protected:
	int looper_max_;//エフェクトループの最大
	int looper_count_;//ループカウント(最大はループ最大数の二倍であることに注意)
	float time_per_loop_harf_;//0.5ループあたりの時間
	float time_count_;//時間カウント
	AlphaNode* alpha_node_;//アルファチャンネル


	//更新(更新するときの時間)
	void Update(float delta_time) override;
	//描画(描画先)
	void Draw(int screen_handle, Camera* camera) override;

public:
	//コンストラクタ
	LineEffect(float x, float y, float last_pos_x, float last_pos_y, unsigned int color_code, float thick , int looper , float time);
	
	//セッター
	void SetAlphaNode(AlphaNode* alpha) { alpha_node_ = alpha; };
};