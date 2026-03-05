//-----------------------------
// @name   object_common.h
// @brief  オブジェクト共通 クラス
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __OBJECT_COMMON_H__
#define __OBJECT_COMMON_H__

#include "..\..\110_drawing_tools\graph_node.h"
#include "hit_box.h"
class ObjectCommon:public GraphNode
{
	HitBox hit_box_; //当たり判定
	bool hit_use_; //判定を使うか
public:
	//コンストラクタ
	ObjectCommon(const char* name, float x, float y, float hit_size_x, float hit_size_y) :GraphNode(name, x, y), hit_box_(x, y, hit_size_x, hit_size_y) { hit_use_ = true; };
	ObjectCommon(const char* name, float x, float y) :GraphNode(name, x, y), hit_box_(x, y, 0.0f, 0.0f) { hit_use_ = false; };
	

	//当たり判定
	HitBox* GetHitBox() { return &hit_box_; };//判定に使う数値
	bool IsObject() { return hit_use_; };//物として扱うものか
	//実際の当たり判定
	bool IsHit(ObjectCommon* other);
};



#endif // !__OBJECT_COMMON_H__
