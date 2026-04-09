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
#include "menu_scene.h"

#include "..\110_drawing_tools\text_node.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\110_drawing_tools\box_node.h"
#include "result_scene.h"
#include "background_node.h"
#include "..\130_data_manager\131_character\object_common.h"
#include "..\130_data_manager\131_character\player_object.h"
#include "..\130_data_manager\131_character\enemy_object.h"
#include "..\130_data_manager\131_character\enemy_manager.h"
#include "..\130_data_manager\132_shots\shot_manager.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\134_other\configs_manager.h"
#include "..\130_data_manager\134_other\score_manager.h"
#include "..\130_data_manager\134_other\txt_font_manager.h"
#include "..\140_roading_from_other\file_roader.h"
#include "..\150_effect\field_effect.h"


void GameScene::SceneCheck() {

	//playフェーズでPボタンが押されたら一時停止
	if ((fase_ == k_play) && Inputer::GetInstance()->GetDownKey(KEY_INPUT_P))
	{
		MusicManager::GetInstance()->StopMusic();
		fase_ = k_stop;

	}
	else if ((fase_ == k_stop) && Inputer::GetInstance()->GetDownKey(KEY_INPUT_P))//stopフェーズでPボタンが押されたら再開
	{
		fase_ = k_restart;
	}
	else if ((fase_ == k_stop) && Inputer::GetInstance()->GetDownKey(KEY_INPUT_Q))//stopフェーズでQボタンが押されたら終了
	{
		//曲を止めてスコアリセット
		MusicManager::GetInstance()->StopMusic();
		ScoreManager::GetInstance()->Reset();
		next_scene_ = new SelectScene();
		MusicManager::GetInstance()->PlayBgm();

	}
	//restartフェーズでカウントが終われば再開
	if ((fase_ == k_restart) && restart_count_ <= window_setting::null_param) {
		fase_ = k_play;
		restart_count_ = system_set::restart_count_up; //再開用のカウントをリセット
		MusicManager::GetInstance()->RePlayMusic();
	}

	//playフェーズで曲を流す時間を過ぎたら曲を止める
	if ((fase_ == k_play) && (MusicManager::GetInstance()->GetMusicTime() * system_set::ms_per_s < last_time_))
	{
		ScoreManager::GetInstance()->ResultLock();
		MusicManager::GetInstance()->StopMusic();
		fase_ = k_end;
		last_time_ = NULL;
		root_->AddChild(end_game_);
	}
	//endフェーズで一定時間になったら結果を出す
	if ((fase_ == k_end) && (system_set::wait_end_time < last_time_)) {

		next_scene_ = new ResultScene();
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

void GameScene::RestartTextUpdate()
{

	Node* new_text_ = new Node();

	//テキストデータ作成
	std::string txts = std::to_string(restart_count_ / system_set::ms_per_s + 1);
	//サイズ確認
	int text_length = GetDrawStringWidth(txts.c_str(), -1);

	new_text_->AddChild(new TextFormatNode(txts.c_str(), GetColor(255, 0, 255), TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1),
		window_setting::center_x - text_length / 2 , window_setting::center_y));

	//元々根ノードがあるなら削除
	if (restart_text_ != nullptr) {

		delete restart_text_;

	}

	restart_text_ = new_text_;

}


void GameScene::Init()
{
	
	//フェーズの切り替え
	fase_ = k_play;

	root_ = new Node();
	end_game_ = new Node();
	restart_text_ = new Node();
	check_text_ = new Node();

	root_->AddChild(new BackgroundNode("200_resource\\back_tree.png", {NULL,NULL}));
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

	//確認ポップアップ作成
	BoxNode* back_box = new BoxNode({ window_setting::center_x-window_setting::pop_up_size_x/2,window_setting::center_y - window_setting::pop_up_size_y / 2 }, 
		{ window_setting::pop_up_size_x ,window_setting::pop_up_size_y },GetColor(230,230,250),NULL,true);
	int i = 0;//個数カウント
	for (auto txt : string_set::continue_check) {
		i++;
		back_box->AddChild(new TextNode(txt, GetColor(0, 0, 0),
			window_setting::pop_up_size_x / 4, line_set::brank_y*i - ege_set::brank_y+window_setting::pop_up_size_y/3));
	}
	check_text_->AddChild(back_box);

	//テキスト更新
	TextUpdate();
	end_game_->AddChild(new TextNode(string_set::game_finish, GetColor(255, 255, 255),
		window_setting::center_x, window_setting::center_y));

	next_scene_ = this;
}

void GameScene::SetUp()
{
	//bgmを止める
	MusicManager::GetInstance()->StopBgm();
	root_->LoadResourceAll();
	root_->SetUpAll();
	end_game_->LoadResourceAll();
	end_game_->SetUpAll();
	//楽曲再生
	ConfigsManager::GetInstance()->SetMusic();
	MusicManager::GetInstance()->PlayMusic();
}

Scene* GameScene::Update(float delta_time) {
	//プレイ中の更新処理
	//時間更新
	//再開フェーズで再開用カウントを加算
	if (fase_ == k_restart)
	{
		restart_count_ -= delta_time;
	}
	else if (fase_ != k_stop) //停止と再開以外で通常のカウントを加算
	{
		last_time_ += delta_time;
	}

	camera_->Update();
	//プレイ中か
	if (fase_ == k_play) {
		

		TextUpdate();
		root_->UpdateAll(delta_time);
		
		root_->SetWorldPositionAll();
		shot_manage_->ShotIn(camera_);
		enemy_->HitEnemies(player_);

	}
	//停止中か
	if (fase_ == k_stop)
	{
		check_text_->UpdateAll(delta_time);
		check_text_->SetWorldPositionAll();
	}
	// 再開中か
	if (fase_ == k_restart) {
		RestartTextUpdate();
		restart_text_->UpdateAll(delta_time);
		restart_text_->SetWorldPositionAll();
	}

	//プレイ終了か
	if (fase_ == k_end) {
		end_game_->UpdateAll(delta_time);
		end_game_->SetWorldPositionAll();
	}

	SceneCheck();


	return next_scene_;
}


void GameScene::Draw(int screen_handle) {

	root_->DrawAll(screen_handle,camera_);
	// 再開中か
	if (fase_ == k_restart) {
		restart_text_->DrawAll(screen_handle, camera_);
	}
	//停止中か
	if (fase_ == k_stop)
	{
		check_text_->DrawAll(screen_handle, camera_);
	}

}


void GameScene::Finalize()
{
	root_->ReleaseResourceAll();
	MusicManager::GetInstance()->DeleteMusic();

}

