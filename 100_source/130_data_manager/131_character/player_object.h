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
class PlayerObject:public ObjectCommon
{
	static PlayerObject* player_;
protected:
	PlayerObject();
public:
	//内容取得
	static PlayerObject* GetInstance();
	Vector2D GetCenter() { return { world_position_.x_ + size_x_ / 2,world_position_.y_ + size_y_ / 2 }; };
	//更新(更新するときの時間)
	void Update(float delta_time);
};
#endif // !__PLAYER_OBJECT_H__



