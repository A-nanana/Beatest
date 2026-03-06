//-----------------------------
// @name   shot_manager.cpp
// @brief  弾オブジェクト管理 クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "shot_manager.h"

#include "shot_object.h"
#include "..\131_character\player_object.h"
#include "..\131_character\enemy_object.h"

//ロード
void ShotManager::Load() {
	shot_graph_handle_.push_back(LoadGraph("..\\..\\200_resource\\bullet.png"));
	
}
//リソース解放
void ShotManager::Release() {
	for (int i = 0; i < shot_graph_handle_.size(); i++) {
		DeleteGraph(shot_graph_handle_[i]);
	}
}
//更新(更新するときの時間)
void ShotManager::Update(float delta_time) {

	for (Node* node : children_) {
		ShotObject* shot = dynamic_cast<ShotObject*>(node);
		if (!shot) {
			continue;
		}
		if (!shot->IsUsed()) {
			
			continue;
		}

		
		if (shot->IsHit(player_)) {
			DeleteChild(shot);
		};
	}
}
//セット
void ShotManager::SetUp() {
	SetPosition(NULL, NULL);
}

//コンストラクタ
ShotManager::ShotManager()
{
	change_time_ = 0;
}

//  セッター
void ShotManager::SetPlayerObject(PlayerObject* player)
{
	player_ = player;
}
void ShotManager::SetEnemyObject(EnemyObject* enemy)
{
	enemy_ = enemy;
}
Vector2D ShotManager::GetPlayerObjectPos()
{
	return player_->GetWorldPosition();
}
//追加
void ShotManager::AddChild(ShotObject* node)
{
	Node::AddChild(node);
}

void ShotManager::AddShot(float x, float y, float speed, float angle)
{
	Node::AddChild(new ShotObject(shot_graph_handle_.front(), x, y, speed, angle));
}
