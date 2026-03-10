//-----------------------------
// @name   shot_manager.h
// @brief  弾オブジェクト管理 クラス
// @auther A.namami
// @date   2026/3/5  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __SHOT_MANAGER_H__
#define __SHOT_MANAGER_H__

#include <vector>
#include "..\..\110_drawing_tools\node.h"
#include "..\131_character\player_object.h"
#include "..\131_character\enemy_object.h"

class EnemyObject;
class PlayerObject;
class ShotObject;
class Camera;

class ShotManager:public Node
{
	std::vector<int> shot_graph_handle_;//弾画像のハンドル
	int size_x_, size_y_;//弾画像のサイズ
	PlayerObject* player_;//使うプレイヤー
	EnemyObject* enemy_;//使う敵

protected:
	//ロード
	void Load();
	//リソース解放
	void Release();
	//更新(更新するときの時間)
	void Update(float delta_time);
	//セット
	void SetUp();
public:
//  コンストラクタ
	ShotManager();
//  セッター
	void SetPlayerObject(PlayerObject* player);
	void SetEnemyObject(EnemyObject* enemy);
//  ゲッター
	Vector2D GetPlayerObjectPos();
	Vector2D GetPlayerCenter() { return player_->GetCenter(); };

//  追加
	void AddChild(ShotObject* node);
	void AddShot(float x, float y, float speed, float angle);
//  ショット更新
	void ShotIn(Camera* camera);

};

#endif // !__SHOT_MANAGER_H__
