//-----------------------------
// @name   player_object.h
// @brief  プレイヤーオブジェクト クラス
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __PLAYER_OBJECT_H__
#define __PLAYER_OBJECT_H__

#include "object_common.h"
#include "../../110_drawing_tools/defining.h"
#include "../../110_drawing_tools/Vector2.h"

class PlayerEffect;

class PlayerObject:public ObjectCommon
{
	static PlayerObject* player_; //インスタンス

	Vector2D last_pos_;//直前位置

	PlayerEffect* effect_;//エフェクトの根

	int is_effect_; //エフェクトが必要か

	//コンストラクタ
	PlayerObject();
	//デストラクタ
	~PlayerObject() {};

public:	
//  複製防止
	PlayerObject operator= (const PlayerObject&) = delete;
	PlayerObject& operator= (PlayerObject&) = delete;


	//内容取得
	static PlayerObject* GetInstance();//インスタンス
	Vector2D GetCenter() { return { world_position_.x_ + size_x_ / 2,world_position_.y_ + size_y_ / 2 }; }; //中心
	
	//直前位置に移動
	void BackLastPos() { world_position_.Set(last_pos_);  }
	//更新(更新するときの時間)
	void Update(float delta_time)override;
	//セットアップ
	void SetUp() override;
	//エフェクトフラグを立てる
	void SetEffect(int flg) { is_effect_ |= flg; };
	//エフェクトフラグを寝かす
	void RestEffect(int flg) { is_effect_ &= ~flg; };


};
#endif // !__PLAYER_OBJECT_H__



