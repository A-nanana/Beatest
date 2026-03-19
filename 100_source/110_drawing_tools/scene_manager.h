//-----------------------------
// @name   scene_manager.h
// @brief  シーン クラスの宣言部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once
#include "scene.h"
#include "graph_node.h"
#include <memory> //ダブり回避用
#include <vector>

class Scene;
class SceneManager
{
	//シーンの移り変わり
	enum Phase {
		kRun = 0, //稼働中
		kSwitch, //切り替え
		kWaitLoad, //ロード待ち
	};
	std::unique_ptr<Scene> now_scene_;//今のシーン
	std::unique_ptr<Scene> next_scene_;//次のシーン
	Phase switch_scene_;//シーン切り替え状態
	GraphNode* wait_load_;//ロード待ち画面

public:
//  コンストラクタ
	SceneManager();

//  デストラクタ
	~SceneManager();

//  更新
	void Update(float delta_time);
//  描画
	void Draw(int screen_handle);
//  シーンセット
	void SetNextScene(Scene* scene);
};

