//-----------------------------
// @name   scene.h
// @brief  シーン クラスの宣言部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once
#include "defining.h"
#include "camera.h"

//操作順位としてどこに置くかのタグ
enum PositionTag {
	next_returner = 1 << 0,//元に戻す必要あり
};

class Scene
{
protected:
	Camera* camera_;//描画の中心を保存する
	Scene* to_return_scene_;// 戻る場合のシーン

	PositionTag tag_;//位置タグ
public:
//  コンストラクタ
	Scene():to_return_scene_(nullptr) { tag_ = (PositionTag)NULL; };
//  デストラクタ
	virtual ~Scene() {};

//  初期化
	virtual void Init() = 0;
//  準備
	virtual void SetUp() = 0;
//  終了
	virtual void Finalize() = 0;
//  更新
	virtual Scene* Update(float delta_time) = 0;
//  描画
	virtual void Draw(int screen_handle) = 0;
//  タグ取得
	PositionTag GetTag() { return tag_; };
//  戻すシーンの取り込み
	void SetToReturnScene(Scene* scene_target) { to_return_scene_ = scene_target; };
//  戻すシーンの取得
	Scene* GetToReturnScene() { return to_return_scene_; };
};

