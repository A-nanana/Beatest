//-----------------------------
// @name   game_scene.h
// @brief  シーン クラスの宣言部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>
#include "game_scene.h"
#include "buttom_node.h"
#include "text_node.h"
#include "..\130_data_manager\131_character\object_common.h"
#include "..\130_data_manager\131_character\player_object.h"
#include "inputer.h"

void GameScene::PushCheck() {
	next_scene_ = new GameScene2();

}


void GameScene::Init()
{
	root_ = new Node();
	camera_ = new Camera(NULL,NULL);
	next_buttom_ = new ButtomNode(1000, 1000, 10.0f, 10.0f, std::bind( &GameScene::PushCheck,this), false);
	next_buttom_->AddChild(new TextNode("押し", GetColor(255, 255, 255), 0.0f, 0.0f));
	Node* ko2 = new TextNode("テストテスト", GetColor(255, 255, 255), window_setting::size_x -10.0f, window_setting::size_y - 10.0f);
	
	root_->AddChild(ko2);
	root_->AddChild(PlayerObject::GetInstance());

	next_scene_ = this;
}

void GameScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetWorldPositionAll();

	next_buttom_->LoadResourceAll();
	next_buttom_->SetWorldPositionAll();
}

Scene* GameScene::Update(float delta_time) {
	camera_->Update();

	root_->UpdateAll(delta_time);

	next_buttom_->UpdateAll(delta_time);

	return next_scene_;
}


void GameScene::Draw(int screen_handle) {

	root_->DrawAll(screen_handle,camera_);
	
	next_buttom_->DrawAll(screen_handle,camera_);
}


void GameScene::Finalize()
{
	root_->ReleaseResourceAll();
	next_buttom_->ReleaseResourceAll();
}

//ここから下はテスト用!

void GameScene2::PushCheck() {

	next_scene_ = new GameScene();
}



void GameScene2::Init()
{
	root_ = new Node();
	camera_ = new Camera(NULL,NULL);

	next_buttom_ = new ButtomNode(1000, 1000, 10.0f, 10.0f, std::bind ( &GameScene2::PushCheck ,this), false);
	next_buttom_->AddChild(new TextNode("押し", GetColor(255, 255, 255), 0.0f, 0.0f));
	Node* ko2 = new TextNode("テストちゅ", GetColor(255, 255, 255), 150.0f, 150.0f);
	next_scene_ = this;

	root_->AddChild(ko2);
	camera_->Init();
}

void GameScene2::SetUp()
{
	root_->LoadResourceAll();
	root_->SetWorldPositionAll();

	next_buttom_->LoadResourceAll();
	next_buttom_->SetWorldPositionAll();
}

Scene* GameScene2::Update(float delta_time) {

	root_->UpdateAll(delta_time);
	camera_->Update();
	next_buttom_->UpdateAll(delta_time);


	return next_scene_;
}


void GameScene2::Draw(int screen_handle) {
	root_->DrawAll(screen_handle,camera_);
	next_buttom_->DrawAll(screen_handle,camera_);
}


void GameScene2::Finalize()
{
	root_->ReleaseResourceAll();
	next_buttom_->ReleaseResourceAll();
}