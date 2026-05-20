//-----------------------------
// @name   field_effect.h
// @brief  舞台エフェクト管理 クラス
// @auther A.namami
// @date   2026/3/12  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __FIELD_EFFECT_H__
#define __FIELD_EFFECT_H__

#include "../110_drawing_tools/alpha_node.h"

//------------------------------
// @name   BackBeatEffect
// @brief  背景ラインエフェクト
// @memo   
//------------------------------
class BackBeatEffect :public AlphaNode {
protected:
	
	float time_per_loop_;//1ループあたりの時間
	float time_count_;//時間カウント
	float max_size_;//最大の大きさ
	int beat_time_;//拍数

	
	//更新(更新するときの時間)
	void Update(float delta_time)override;
public:
	//コンストラクタ
	BackBeatEffect(int time_per_loop, int beat_time,Vector2D vector_point);
	

};

//------------------------------
// @name   FieldEffect
// @brief  背景のエフェクト管理 
// @memo   
//------------------------------
class FieldEffect:public Node
{
protected:
	
public:
	FieldEffect();
};


#endif // !__FIELD_EFFECT_H__
