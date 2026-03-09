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
#include "..\130_data_manager\131_character\enemy_object.h"
#include "..\130_data_manager\132_shots\shot_manager.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\140_roading_from_other\file_roader.h"
#include "inputer.h"

void GameScene::PushCheck() {

}


void GameScene::Init()
{
	root_ = new Node();
	camera_ = new Camera();
	next_buttom_ = new ButtomNode(1000, 1000, 10.0f, 10.0f, std::bind( &GameScene::PushCheck,this), false);
	next_buttom_->AddChild(new TextNode("押し", GetColor(255, 255, 255), 0.0f, 0.0f));
	Node* ko2 = new TextNode("テストテスト", GetColor(255, 255, 255), window_setting::size_x -10.0f, window_setting::size_y - 10.0f);
	
	player_ = PlayerObject::GetInstance();
	player_->SetPosition(window_setting::size_x -100 , window_setting::size_y -100);

	shot_manage_ = new ShotManager();
	enemy_ = new EnemyObject(shot_manage_,FileRoader::GetInstance()->RoadHumen(MusicManager::GetInstance()->GetMusicData()));

	root_->AddChild(ko2);
	root_->AddChild(player_);
	root_->AddChild(enemy_);
	root_->AddChild(shot_manage_);

	shot_manage_->SetPlayerObject(player_);
	shot_manage_->SetEnemyObject(enemy_);

	next_scene_ = this;
}

void GameScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();

	next_buttom_->LoadResourceAll();
	MusicManager::GetInstance()->PlayMusic();
}

Scene* GameScene::Update(float delta_time) {
	camera_->Update();
	root_->UpdateAll(delta_time);
	root_->SetWorldPositionAll();
	shot_manage_->ShotIn(camera_);


	next_buttom_->SetWorldPositionAll();
	next_buttom_->UpdateAll(delta_time);
	next_buttom_->SetWorldPositionAll();


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
	MusicManager::GetInstance()->DeleteMusic();
}

//ここから下はテスト用!
