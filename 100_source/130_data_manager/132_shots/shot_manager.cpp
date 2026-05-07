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
#include "../131_character/player_object.h"
#include "../131_character/enemy_manager.h"
#include "../../110_drawing_tools/camera.h"
#include "../134_other/score_manager.h"
#include "../134_other/window_manager.h"
#include "../133_music/music_manager.h"
#include "../../140_roading_from_other/graph_roader.h"

std::unordered_map<std::string, int>  ShotManager::graph_;
//ロード
void ShotManager::Load() {
	//画像読み込み
	graph_.insert({ file_set::lazer, GraphRoader::GetInstance()->RoadingGraph(file_set::lazer) });
	graph_.insert({ file_set::shot, GraphRoader::GetInstance()->RoadingGraph(file_set::shot) });
	per_time_ = MusicManager::GetInstance()->GetMsPerHyousi();
	long_time_ = 0;
}
//リソース解放
void ShotManager::Release() {
	
}
//更新(更新するときの時間)
void ShotManager::Update(float delta_time) {
	//ノード分繰り返す
	for (Node* node : children_) {

		ShotObject* shot = dynamic_cast<ShotObject*>(node);
		//オブジェクトがあるか
		if (!shot) {
			continue;
		}
		//レーザーか
		
		bool is_lazer = (shot->GetType() == system_set::k_enemy_lazer);
		
		//オブジェクトが有効か
		if (!(shot->IsUsed())) {
			//レーザーならカウント
			if (is_lazer) {
				ScoreManager::GetInstance()->ScoreUpdate(k_lazer_none);
			}
			//有効でないならとり除く
			DeleteChild(shot);
			continue;
		}
		//当たり判定が必要ないか
		if (!shot->IsObject()) {
			continue;
		}

		//当たっているか
		if (player_->IsHit(shot) || (is_lazer && shot->IsHit(player_))) {
				//エフェクトのフラグを立てる
			player_->SetEffect(effect_set::effect_critical);

			//コンボの消去
			ScoreManager::GetInstance()->ScoreUpdate(k_miss);
			//存在フラグ切り替え(レーザーは除く)
			shot->ChangeUsed();
			
		}
		
		//判定距離で分岐
		if( (player_->GetDistance() < system_set::critical_hit_check*system_set::critical_hit_check)
			&&(shot->GetCenter().Length_2zyou() > player_->GetCenter().Length_2zyou()))//クリティカルの範囲かつ弾がプレイヤーの奥にある
		{
			//エフェクトのフラグを立てる
			player_->SetEffect(effect_set::effect_critical);
			//クリティカル加算
			ScoreManager::GetInstance()->ScoreUpdate(k_critical);
			//存在フラグ切り替え
			shot->ChangeUsed();
			
		}
		else if ((player_->GetDistance() < system_set::start_hit_check* system_set::start_hit_check) &&
			(shot->GetCenter().Length_2zyou() > player_->GetCenter().Length_2zyou()) ) //判定開始ライン かつ　弾が奥にある
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
		
		//弾のキャスト
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
			continue;
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
		//時差打ちか通常 
		if ((type == system_set::k_enemy_nomal) || (type == system_set::k_enemy_later_renge)) {
			Node::AddChild(new ShotObject(graph_[file_set::shot], x, y, speed, angle, GetPlayerCenter(), type));
		}
		//一周打ち
		if (type == system_set::k_enemy_all_renge) {
			Node::AddChild(new ShotObject(graph_[file_set::shot], x, y, speed, angle, { WindowManager::GetInstance()->GetWindowLength() * cos(angle), WindowManager::GetInstance()->GetWindowLength() * sin(angle) },type));
		}
		//レーザー
		if (type == system_set::k_enemy_lazer) {

			Node::AddChild(new LongShot(graph_[file_set::lazer],window_setting::null_param,window_setting::null_param, speed, angle, GetPlayerCenter(), type));

		}
		
	}
}
