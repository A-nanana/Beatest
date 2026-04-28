//-----------------------------
// @name   enemy_manager.h
// @brief  敵オブジェクト管理 クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __ENEMY_MANAGER_H__
#define __ENEMY_MANAGER_H__

#include "..\..\110_drawing_tools\node.h"

class ShotManager;
class EnemyObject;
class ObjectCommon;

class EnemyManager:public Node
{
	ShotManager* shot_manage_;//弾の管理
	float change_time_;//変化用の時間

protected:
	//ロード
	void Load()override;
	//リソース解放
	void Release()override;
	//更新(更新するときの時間)
	void Update(float delta_time)override;
	//セット
	void SetUp()override;
public:
	//  コンストラクタ
	EnemyManager();
	//  セッター
	void SetShotManager(ShotManager* shot_manage);
	//  本体当たり判定
	bool HitEnemies(ObjectCommon* object);

	//  追加
	void AddChild(EnemyObject* node);

};
#endif // ! __ENEMY_MANAGER_H__
