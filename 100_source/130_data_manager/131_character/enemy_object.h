//-----------------------------
// @name   enemy_object.h
// @brief  敵オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __ENEMY_OBJECT_H__
#define __ENEMY_OBJECT_H__

#include "object_common.h"
class ShotManager;
class EnemyObject :public ObjectCommon
{
protected:
	ShotManager* shot_manager_;
public:
	EnemyObject(ShotManager* shot_manager);
	//更新(更新するときの時間)
	void Update(float delta_time);
};
#endif // !__ENEMY_OBJECT_H__


