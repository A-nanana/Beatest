//-----------------------------
// @name   game_scene.h
// @brief  シーン クラスの宣言部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

#include "node.h"
#include "scene.h"

class ButtomNode;
class GameScene:public Scene
{
	

	Scene* next_scene_;//次のシーン

	Node* root_;//根ノード作成

	ButtomNode* next_buttom_;//遷移用ボタン


public:

	//関数
	void PushCheck();

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

class GameScene2 :public Scene
{
	

	Scene* next_scene_;

	Node* root_;//根ノード作成

	ButtomNode* next_buttom_;//遷移用ボタン

public:
	//関数
	void PushCheck();
	GameScene2() {};
	//  デストラクタ
	~GameScene2() {};

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


