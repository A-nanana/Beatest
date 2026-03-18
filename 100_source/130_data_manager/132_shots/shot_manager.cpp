//-----------------------------
// @name   shot_manager.cpp
// @brief  弾オブジェクト管理 クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//         比較は二乗比較
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include <iostream>
#include "DxLib.h"
#include "shot_manager.h"

#include "shot_object.h"
#include "..\131_character\player_object.h"
#include "..\131_character\enemy_manager.h"
#include "..\..\110_drawing_tools\camera.h"
#include "..\134_other\score_manager.h"

//ロード
void ShotManager::Load() {
	shot_graph_handle_.push_back(LoadGraph("200_resource\\bullet.png"));
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
		//オブジェクトがあるか
		if (!shot) {
			continue;
		}
		//オブジェクトが有効か
		if (!(shot->IsUsed())) {
			//有効でないならとり除く
			DeleteChild(shot);
			continue;
		}

		//当たっているか
		if (player_->IsHit(shot)) {
			//コンボの消去
			ScoreManager::GetInstance()->ScoreUpdate(k_miss);
			//存在フラグ切り替え
			shot->ChangeUsed();
			
		}
		
		//判定距離で分岐
		else if( (player_->GetDistance() < system_set::critical_hit_check*system_set::critical_hit_check)
			&& shot->GetCenter().Length_2zyou() >= player_->GetCenter().Length_2zyou())//クリティカルの範囲かつ弾がプレイヤーの距離を超える
		{
			//エフェクトのフラグを立てる
			player_->SetEffect(effect_set::effect_critical);
			//クリティカル加算
			ScoreManager::GetInstance()->ScoreUpdate(k_critical);
			//存在フラグ切り替え
			shot->ChangeUsed();
			
		}
		else if (player_->GetDistance() < system_set::start_hit_check* system_set::start_hit_check &&
			shot->GetCenter().Length_2zyou() >= player_->GetCenter().Length_2zyou()) //判定開始ライン かつ　弾が奥にある
		{
			//エフェクトのフラグを立てる
			player_->SetEffect(effect_set::effect_avoid);
			//スコア加算
			ScoreManager::GetInstance()->ScoreUpdate(k_great);
			//存在フラグ切り替え
			shot->ChangeUsed();
		

		}
	
	}
	//位置確認
	//敵と当たっていたら直前位置に移動
	if (enemy_->HitEnemies(player_)) {
		player_->BackLastPos();
	}

}
void ShotManager::ShotIn(Camera* camera)
{
	for (Node* node : children_) {
		ShotObject* shot = dynamic_cast<ShotObject*>(node);
		//オブジェクトがあるか
		if (!shot) {
			continue;
		}
		//カメラに入っているか
		if (!camera->IsDraw(shot->GetWorldPosition())) {
			//スコア加算
			ScoreManager::GetInstance()->ScoreUpdate(k_none);
			//存在フラグ切り替え
			shot->ChangeUsed();
			

		}
	}
}
//セット
void ShotManager::SetUp() {
	SetPosition(NULL, NULL);
}

//コンストラクタ
ShotManager::ShotManager()
{
}

//  セッター
void ShotManager::SetPlayerObject(PlayerObject* player)
{
	player_ = player;
}
void ShotManager::SetEnemyManager(EnemyManager* enemy)
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

void ShotManager::AddShot(float x, float y, float speed, float angle, int type)
{
	//存在できるか
	if (children_.size() < system_set::shot_max) {
		//タイプで分けて追加
		if (type == system_set::k_enemy_nomal) {
			Node::AddChild(new ShotObject(shot_graph_handle_.front(), x, y, speed, angle, GetPlayerCenter(),type));
		}
		if (type == system_set::k_enemy_all_renge) {
			Node::AddChild(new ShotObject(shot_graph_handle_.front(), x, y, speed, angle, { window_setting::length * cos(angle),window_setting::length * sin(angle) },type));
		}
	}
}
