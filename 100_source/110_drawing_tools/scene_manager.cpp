//-----------------------------
// @name   scene_manager.cpp
// @brief  シーン クラスの実装部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "DxLib.h"
#include "scene_manager.h"

SceneManager::SceneManager()
{
	now_scene_ = nullptr;
	next_scene_ = nullptr;
	switch_scene_ = kRun;
}

SceneManager::~SceneManager()
{
}


void SceneManager::Update(float delta_time) {
	Scene* next;

// 状態で変化させる
	switch (switch_scene_)
	{
	case Phase::kRun:
		next = now_scene_->Update(delta_time);
		//ポインタが同一か
		if (next != now_scene_.get()) {
			SetNextScene(next);
		}
		break;
	case Phase::kSwitch:
		//ポインタの有無
		if (now_scene_ != nullptr) {
			//古いシーンを解除
			now_scene_->Finalize();
			now_scene_.reset();
		}
		//次のシーンを今のシーンに切り替え
		now_scene_ = std::move(next_scene_);

		//次に進める
		switch_scene_ = Phase::kWaitLoad;

		break;
	case Phase::kWaitLoad:
		//ロード中の物がないか(他のロード物の有無)
		if (GetASyncLoadNum() == 0) {
			now_scene_->SetUp();
			switch_scene_ = Phase::kRun;
		}

		break;

	default:
		break;
	}

}

void SceneManager::Draw(int screen_handle) {
	switch (switch_scene_)
	{
	case Phase::kRun:
		now_scene_->Draw(screen_handle);
		break;
	case Phase::kSwitch:
	case Phase::kWaitLoad:
		break;
	default:
		break;
	}
}


void SceneManager::SetNextScene(Scene* scene) {
	next_scene_.reset(scene);//シーン代入
	next_scene_->Init();//シーン初期化

	switch_scene_ = Phase::kSwitch; //状態切り替え
}
