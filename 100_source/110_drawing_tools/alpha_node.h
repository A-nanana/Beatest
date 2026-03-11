//-----------------------------
// @name   alpha_node.h
// @brief  アルファノード クラスの宣言部
// @auther A.namami
// @date   2026/3/11  新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once
#include "node.h"

class AlphaNode:public Node
{
	float alpha_;//アルファチャンネル
	
protected:
	//描画(描画先)
	void Draw(int screen_handle, Camera* camera) override;

public:
//  コンストラクタ
	AlphaNode(float alpha) :alpha_(alpha) {};
//  セッター
	void SetAlpha(float alpha) { alpha_ = alpha; }; //アルファ値
//  ゲッター
	float GetAlpha() { return alpha_; };//アルファ値

//  加減算
	void Add(float param) { alpha_ += param; };// 加算
	void Sub(float param) { alpha_ -= param; };// 減算
};

