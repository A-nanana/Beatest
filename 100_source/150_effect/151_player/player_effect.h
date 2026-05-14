//-----------------------------
// @name   player_effect.h
// @brief  プレイヤーエフェクト クラス
// @auther A.namami
// @date   2026/3/11  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __PLAYER_EFFECT_H__
#define __PLAYER_EFFECT_H__

#include "..\..\110_drawing_tools\node.h"
#include "..\..\110_drawing_tools\alpha_node.h"

class PlayerObject;
//------------------------------
// @name   HitLineEffect
// @brief  ラインヒットエフェクト
// @memo   
//------------------------------
class HitLineEffect :public AlphaNode {

protected:
	int looper_max_;//エフェクトループの最大
	int looper_count_;//ループカウント(最大はループ最大数の二倍であることに注意)
	float time_per_loop_harf_;//0.5ループあたりの時間
	float time_count_;//時間カウント
	unsigned int color_code_;//エフェクトの色
	int eff_type_;//エフェクト種類

	//更新(更新するときの時間)
	void Update(float delta_time)override;
public:
//  コンストラクタ
	HitLineEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size, int red, int green, int blue, int type);
	HitLineEffect(int loop_max, int time_per_loop, Vector2D vector_point, Vector2D size, int color_code ,int type);

//  位置設定(第一引数で中心を渡すこと)
	void SetEffPositon(Vector2D player_point, Vector2D graph_size);
//  終了確認
	bool IsEnd() { return looper_count_ > looper_max_; };

//  フラグ取得
	int GetFlg() { return eff_type_; };
};


//------------------------------
// @name   PlayerEffect
// @brief  プレイヤーのエフェクト管理 
// @memo   
//------------------------------
class PlayerEffect:public Node
{
protected:
	int flg_;//今あるエフェクト
	PlayerObject* player_; //プレイヤー

	//セット
	void SetUp()override;
	//更新(更新するときの時間)
	void Update(float delta_time)override;
	
public:
//  コンストラクタ
	PlayerEffect(PlayerObject* player);
	
//  エフェクト作成(対応フラグ)
	void Create(int flg);
};


#endif // !__PLAYER_EFFECT_H__
