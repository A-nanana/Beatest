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

#include "../../110_drawing_tools/graph_node.h"
#include "../../110_drawing_tools/defining.h"

class ObjectCommon:public GraphNode
{
protected:
	Vector2D point_[hit_set::squair_point]; //頂点
	Vector2D vectol_[hit_set::squair_point]; //各頂点のベクトル
	Vector2D hit_size_;//当たり判定の大きさ
	Vector2D distance_;//当たり判定時の最小距離
	bool hit_use_; //判定を使うか
public:
//  コンストラクタ
	ObjectCommon(const char* name, float x, float y, float hit_size_x, float hit_size_y);
	ObjectCommon(const char* name, float x, float y) :GraphNode(name, x, y), hit_use_(false) {};
	ObjectCommon(const int graph_handle, float x, float y);

//  セッター
	void SetRotate(float angle);//回転
	void SetHitSize(float x, float y);//サイズ
	void SetPosition(const float& x, const float& y);//相対位置
	void SetWorldPosition();//ワールド座標
	void SetAngle(float to_x, float to_y); //x,yの目標地点から

//  ゲッター
	Vector2D GetCenter() { return { world_position_.x_ - size_x_ / 2 , world_position_.y_ - size_y_ / 2 }; };//中心
	const float GetDistance() { return distance_.Length_2zyou(); };//当たり判定時の最小距離の二乗
	const float GetAllLength();//右下端までの距離
	Vector2D* GetPoints() { return point_; };//頂点
	Vector2D GetSize() { return hit_size_; };//大きさ(当たり判定)

	void Load() override;//ロード

	//当たり判定補助
	bool IsObject() { return hit_use_; };//物として扱うものか
	//当たり判定
	bool HitCheckToPoint(Vector2D* other,Vector2D* dist_);//点と辺
	bool HitCheckToBox(ObjectCommon* other);//点と矩形
	//実際の当たり判定
	bool IsHit(ObjectCommon* other);




};



#endif // !__OBJECT_COMMON_H__
