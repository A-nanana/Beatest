//-----------------------------
// @name   tutorial_scene.cpp
// @brief  チュートリアル クラス
// @auther A.namami
// @date   2026/9/1  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "tutorial_scene.h"

void TutorialScene::UpdateTxt()
{
}

void TutorialScene::Init() {


	//ゲームシーン側初期化
	GameScene::Init();

}

void TutorialScene::SetUp()
{
	//ゲームシーン側セットアップ
	GameScene::SetUp();
}

void TutorialScene::Finalize()
{

	//ゲームシーン側ファイナライズ
	GameScene::Finalize();

}

Scene* TutorialScene::Update(float delta_time)
{

	//ゲームシーン側更新
	GameScene::Update(delta_time);

	return next_scene_;
}

void TutorialScene::Draw(int screen_handle)
{
	//ゲームシーン側描画
	GameScene::Draw(screen_handle);

	//チュートリアル文の描画

}
