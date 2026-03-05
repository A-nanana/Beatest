//-----------------------------
// @name   hit_box.h
// @brief  当たり判定 クラス
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __HIT_BOX_H__
#define __HIT_BOX_H__

#include "..\..\110_drawing_tools\Vector2.h"
#include "..\..\110_drawing_tools\Vector3.h"
#include "..\..\110_drawing_tools\defining.h"

class HitBox
{
public:
	Vector2D point_[hit_set::squair_point]; //頂点
	Vector3D vectol_[hit_set::squair_point]; //各頂点のベクトル
	float lotate_rad_;//回転(右回り	)

	//コンストラクタ
	HitBox(float x_start, float y_start, float x_size, float y_size, float lotate_rad = 0.0f);
	//セッター
	void SetToSize(int x, int y);
	//当たり判定
	bool HitCheckToPoint(Vector2D* other);
	bool HitCheckToBox(HitBox* other);

};


#endif // !__HIT_BOX_H__
