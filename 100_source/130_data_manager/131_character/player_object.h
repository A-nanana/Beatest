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
#include "..\..\110_drawing_tools\defining.h"


class PlayerObject:public ObjectCommon
{
	static PlayerObject* player_; //インスタンス

	int is_effect_; //エフェクトが必要か

protected:
	//コンストラクタ
	PlayerObject();
	//デストラクタ
	~PlayerObject() {};

public:	
//  複製防止
	PlayerObject operator= (const PlayerObject&) = delete;
	PlayerObject& operator= (PlayerObject&) = delete;


	//内容取得
	static PlayerObject* GetInstance();
	Vector2D GetCenter() { return { world_position_.x_ + size_x_ / 2,world_position_.y_ + size_y_ / 2 }; };
	//更新(更新するときの時間)
	void Update(float delta_time);
	//セットアップ
	void SetUp() override;
	//エフェクトフラグを立てる
	void SetEffect(int flg) { is_effect_ |= flg; };
	//エフェクトフラグを寝かす
	void RestEffect(int flg) { is_effect_ &= ~flg; };


};
#endif // !__PLAYER_OBJECT_H__



