//-----------------------------
// @name   top_scene.cpp
// @brief  冒頭シーン クラス
// @auther A.namami
// @date   2026/3/9  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>
#include "top_scene.h"
#include "game_scene.h"

#include "..\110_drawing_tools\buttom_node.h"
#include "..\110_drawing_tools\text_node.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\110_drawing_tools\defining.h"
#include "..\120_game_scene\config_scene.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\140_roading_from_other\file_roader.h"

//-----------------------------
// @name   TopScene
// @brief  表紙
// @memo   セットしてから使うこと
//------------------------------

void TopScene::PushCheck() {
	//エンターキーが押されたら遷移
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		next_scene_ = new SelectScene();
	}
}


void TopScene::Init()
{
	root_ = new Node();
	camera_ = new Camera();
	int string_size = GetDrawStringWidth(string_set::title, -1);

	Node* ko2 = new TextNode(string_set::title, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, window_setting::center_y);
	
	root_->AddChild(ko2);
	
	string_size = GetDrawStringWidth(string_set::push_to_start, -1);

	root_->AddChild(new TextNode(string_set::push_to_start, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, window_setting::center_y + line_set::brank_y * 2));
	


	next_scene_ = this;
}

void TopScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();

}

Scene* TopScene::Update(float delta_time) {
	camera_->Update();
	root_->UpdateAll(delta_time);
	root_->SetWorldPositionAll();
	
	PushCheck();

	return next_scene_;
}


void TopScene::Draw(int screen_handle) {

	root_->DrawAll(screen_handle, camera_);


}


void TopScene::Finalize()
{
	root_->ReleaseResourceAll();
}



//-----------------------------
// @name   SelectScene
// @brief  選択シーン
// @memo   セットしてから使うこと
//------------------------------

void SelectScene::PushCheck() {
	//W,Sキーで選択
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)) {
		selecter_--;
	}
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S)) {
		selecter_++;
	}
	//セレクターをループさせる
	selecter_ = (selecter_ + MusicManager::GetInstance()->GetLineupSize()) % MusicManager::GetInstance()->GetLineupSize();
	//エンターで決定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		MusicManager::GetInstance()->SetPlayMusic(MusicManager::GetInstance()->operator[](selecter_).c_str());
		next_scene_ = new GameScene();
	}
	//Escキーで設定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_ESCAPE)) {
		next_scene_ = new ConfigScene();
	}

}

void SelectScene::TextUpdate()
{
	

	Node* new_text_ = new Node();
	new_text_->SetPosition(line_set::selecter_x, line_set::selecter_y);

	//テキストデータ作成
	for (int i = 0; i < line_set::amount_y_max; i++) {
		std::string text = 
			MusicManager::GetInstance()->operator[]((selecter_ - (line_set::amount_y_max / 2 )+ MusicManager::GetInstance()->GetLineupSize()+ i) % MusicManager::GetInstance()->GetLineupSize());
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		new_text_->AddChild(new TextNode(text.c_str(), GetColor(255, 255, 255),
			line_set::brank_x, line_set::brank_y * i));

	}

	//元々根ノードがあるなら削除
	if (text_ != nullptr) {
		
		root_->DeleteChild(text_);
	
	}

	text_ = new_text_;
	root_->AddChild(new_text_);

}

void SelectScene::Init() {
	MusicManager::GetInstance()->SetLineUp();

	root_ = new Node();
	camera_ = new Camera();
	int string_size = GetDrawStringWidth(string_set::select_song, -1);

	Node* ko2 = new TextNode(string_set::select_song, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, line_set::midasi_y);

	root_->AddChild(ko2);
	root_->AddChild(new TextNode("->", GetColor(255, 255, 255), line_set::selecter_x, line_set::selecter_y + line_set::brank_y * 2));
	

	TextUpdate();




	next_scene_ = this;
};

void SelectScene::SetUp() {
	root_->LoadResourceAll();
	root_->SetUpAll();

}

Scene* SelectScene::Update(float delta_time) {
	camera_->Update();
	TextUpdate();

	root_->UpdateAll(delta_time);

	root_->SetWorldPositionAll();

	SelectScene::PushCheck();


	return next_scene_;
}

void SelectScene::Draw(int screen_handle) {
	root_->DrawAll(screen_handle, camera_);

}

void SelectScene::Finalize() {
	root_->ReleaseResourceAll();

}