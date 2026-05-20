//-----------------------------
// @name   enemy_manager.cpp
// @brief  敵オブジェクト管理 クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "enemy_manager.h"
#include "../132_shots/shot_manager.h"
#include "enemy_object.h"

//ロード
void EnemyManager::Load() {

}
//リソース解放
void EnemyManager::Release() {
	
}
//更新(更新するときの時間)
void EnemyManager::Update(float delta_time) {

}
//セット
void EnemyManager::SetUp() {

}

//  コンストラクタ
EnemyManager::EnemyManager()
{
	shot_manage_ = nullptr;
}

//セッター
void EnemyManager::SetShotManager(ShotManager* shot_manage)
{
	shot_manage_ = shot_manage;
}

bool EnemyManager::HitEnemies(ObjectCommon* object)
{
	bool returner = false;//返り値
	//子の数繰り返す
	for (Node* child : children_) {
		ObjectCommon* object_other = dynamic_cast<ObjectCommon*>(child);
		//オブジェクトかどうか
		if (!object_other) {
			continue;
		}
		//当たったか
		if (object->HitCheckToBox(object_other)) {
			
			returner = true;
		}
	}
	return returner;
}

//追加
void EnemyManager::AddChild(EnemyObject* node)
{
	Node::AddChild(node);
}
