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

#include "..\110_drawing_tools\text_node.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\120_game_scene\result_scene.h"
#include "..\120_game_scene\background_node.h"
#include "..\130_data_manager\131_character\object_common.h"
#include "..\130_data_manager\131_character\player_object.h"
#include "..\130_data_manager\131_character\enemy_object.h"
#include "..\130_data_manager\131_character\enemy_manager.h"
#include "..\130_data_manager\132_shots\shot_manager.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\134_other\configs_manager.h"
#include "..\130_data_manager\134_other\score_manager.h"
#include "..\140_roading_from_other\file_roader.h"
#include "..\150_effect\field_effect.h"


void GameScene::SceneCheck() {
	if (MusicManager::GetInstance()->GetMusicTime() * system_set::ms_per_s < last_time_) {
		next_scene_ = new ResultScene();
		ScoreManager::GetInstance()->ResultLock();

	}
}

void GameScene::TextUpdate()
{


	Node* new_text_ = new Node();

	//テキストデータ作成
	new_text_->AddChild(new TextNode(ScoreManager::GetInstance()->GetNowConbo().c_str(), GetColor(255, 0, 255),
		window_setting::center_x , window_setting::center_y));
	//サイズ確認
	int text_length = GetDrawStringWidth(ScoreManager::GetInstance()->GetScore().c_str(), -1);

	new_text_->AddChild(new TextNode(ScoreManager::GetInstance()->GetScore().c_str(), GetColor(255, 0, 255),
		window_setting::size_x - text_length - line_set::brank_x, window_setting::size_y - line_set::brank_y));

	//元々根ノードがあるなら削除
	if (text_ != nullptr) {

		root_->DeleteChild(text_);

	}

	text_ = new_text_;
	root_->AddChild(new_text_);

}


void GameScene::Init()
{
	//bgmを止める
	MusicManager::GetInstance()->StopBgm();

	root_ = new Node();
	root_->AddChild(new BackgroundNode("..\\200_resource\\back_tree.png", {NULL,NULL}));
	camera_ = new Camera();
	
	//中身の設定
	
	//プレイヤー
	player_ = PlayerObject::GetInstance();
	player_->SetPosition(window_setting::center_x , window_setting::center_y + line_set::brank_y);

	//ショットと敵
	shot_manage_ = new ShotManager();
	enemy_ = new EnemyManager();
	enemy_->AddChild(new EnemyObject(shot_manage_,FileRoader::GetInstance()->RoadHumen(MusicManager::GetInstance()->GetMusicData())));

	//ルートノードに追加
	root_->AddChild(new FieldEffect());
	root_->AddChild(player_);
	root_->AddChild(enemy_);
	root_->AddChild(shot_manage_);

	//ショット管理に要素追加
	shot_manage_->SetPlayerObject(player_);
	shot_manage_->SetEnemyManager(enemy_);

	//固定テキストをそのまま追加
	root_->AddChild(new TextNode(string_set::conbo, GetColor(255, 0, 255),
		window_setting::center_x, window_setting::center_y - line_set::brank_y));

	//テキスト更新
	TextUpdate();

	next_scene_ = this;
}

void GameScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();
	ConfigsManager::GetInstance()->SetMusic();
	MusicManager::GetInstance()->PlayMusic();
}

Scene* GameScene::Update(float delta_time) {
	last_time_ += delta_time;
	camera_->Update();
	
	TextUpdate();

	root_->UpdateAll(delta_time);
	root_->SetWorldPositionAll();
	shot_manage_->ShotIn(camera_);
	enemy_->HitEnemies(player_);


	SceneCheck();


	return next_scene_;
}


void GameScene::Draw(int screen_handle) {

	root_->DrawAll(screen_handle,camera_);
	

}


void GameScene::Finalize()
{
	root_->ReleaseResourceAll();
	MusicManager::GetInstance()->DeleteMusic();
}

//ここから下はテスト用!
