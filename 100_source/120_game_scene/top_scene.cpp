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
#include "..\110_drawing_tools\buttom_node.h"
#include "..\110_drawing_tools\text_node.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\140_roading_from_other\file_roader.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\110_drawing_tools\defining.h"

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
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)) {
		selecter_--;
	}
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S)) {
		selecter_++;
	}

	selecter_ = (selecter_ + MusicManager::GetInstance()->GetLineupSize()) % MusicManager::GetInstance()->GetLineupSize();
}

void SelectScene::TextUpdate()
{
	//元々根ノードがあるなら削除
	if (text_ != nullptr) {
		delete text_;
	}

	text_ = new Node();
	text_->SetPosition(ege_set::bar_brank_x, ege_set::bar_brank_y);

	//テキストデータ作成
	for (int i = 0; i < line_set::amount_y_max; i++) {
		std::string text = 
			MusicManager::GetInstance()->operator[]((selecter_ - (line_set::amount_y_max / 2 )+ MusicManager::GetInstance()->GetLineupSize()+ i) % MusicManager::GetInstance()->GetLineupSize());
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		text_->AddChild(new TextNode(text.c_str(), GetColor(255, 255, 255),
			line_set::brank_x, line_set::brank_y * i));

	}

	root_->AddChild(text_);

}

void SelectScene::Init() {
	MusicManager::GetInstance()->SetLineUp();

	root_ = new Node();
	camera_ = new Camera();
	int string_size = GetDrawStringWidth(string_set::title, -1);

	Node* ko2 = new TextNode(string_set::title, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, window_setting::center_y);

	root_->AddChild(ko2);
	

	TextUpdate();




	next_scene_ = this;
};

void SelectScene::SetUp() {
	root_->LoadResourceAll();
	root_->SetUpAll();

}

Scene* SelectScene::Update(float delta_time) {
	camera_->Update();
	root_->UpdateAll(delta_time);
	root_->SetWorldPositionAll();




	return next_scene_;
}

void SelectScene::Draw(int screen_handle) {
	root_->DrawAll(screen_handle, camera_);

}

void SelectScene::Finalize() {
	root_->ReleaseResourceAll();

}