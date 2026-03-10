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

#include "node.h"
#include "scene.h"

class EnemyObject;
class PlayerObject;
class ShotManager;
class GameScene:public Scene
{
	

	Scene* next_scene_;//次のシーン

	Node* root_;//根ノード作成
	Node* text_;//テキスト根ノード

	//それぞれのオブジェクトのポインタ保存用
	EnemyObject* enemy_;
	PlayerObject* player_;
	ShotManager* shot_manage_;

	int last_time_;//時間計測用

public:

	//シーンチェック
	void SceneCheck();
	//テキスト確認
	void TextUpdate();
	//コンストラクタ
	GameScene() {};
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


