//-----------------------------
// @name   effect_dot.h
// @brief  プレイヤーエフェクト 素材 クラス
// @auther A.namami
// @date   2026/6/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __EFFECT_DOT_H__
#define __EFFECT_DOT_H__

#include "../../110_drawing_tools/box_node.h"
class EffectDot :public BoxNode
{
	float rotate_;//回転(及びどこに向かわせるか)
	int it_speed_;//速さ
	

public:
	EffectDot(float rotate, int speed, Vector2D pos, Vector2D size, unsigned int color, float thick, bool is_full = false);
	void Update(float delta_time) override;
};


#endif // !__EFFECT_DOT_H__
