//-----------------------------
// @name   enemy_object.cpp
// @brief  敵オブジェクト クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "enemy_object.h"

EnemyObject::EnemyObject(ShotManager* shot_manager):shot_manager_(shot_manager),
ObjectCommon("..\\200_resource\\enemy.png", 1.0f, 1.0f, 180.0f, 180.0f)
{
	
}

void EnemyObject::Update(float delta_time) {

}

