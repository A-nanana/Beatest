//-----------------------------
// @name   game_scene.h
// @brief  シーン クラスの宣言部
// @auther A.namami
// @date   2026/3/2  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

#include "..\110_drawing_tools\alpha_node.h"
#include "..\110_drawing_tools\scene.h"

class EnemyManager;
class PlayerObject;
class ShotManager;
class GameScene:public Scene
{
	

	Scene* next_scene_;//次のシーン

	Node* root_;//根ノード作成
	Node* text_;//テキスト根ノード
	Node* end_game_;//ゲームセット用根ノード

	//それぞれのオブジェクトのポインタ保存用
	EnemyManager* enemy_;//敵
	PlayerObject* player_;//プレイヤー
	ShotManager* shot_manage_;//弾

	//フェーズ切り替え
	enum Fase {
		k_play, //ゲーム中
		k_end, //終了
	};
	Fase fase_;//今の状態

	int last_time_;//時間計測用

public:

	//シーンチェック
	void SceneCheck();
	//テキスト確認
	void TextUpdate();
	//コンストラクタ
	GameScene() { last_time_ = NULL; };
	//  デストラクタ
	~GameScene() {};

	//  初期化
	void Init();
	//  準備
	void SetUp();
	//  終了
	void Finalize();
	//  更新
	Scene* Update(float delta_time);
	//  描画
	void Draw(int screen_handle);


};


