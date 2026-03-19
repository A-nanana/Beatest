//-----------------------------
// @name   menu_scene.cpp
// @brief  メニューシーン クラス
// @auther A.namami
// @date   2026/3/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <iostream>

#include "menu_scene.h"
#include "game_scene.h"

#include "..\110_drawing_tools\buttom_node.h"
#include "..\110_drawing_tools\text_node.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\110_drawing_tools\defining.h"
#include "..\120_game_scene\config_scene.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\134_other\configs_manager.h"
#include "..\140_roading_from_other\file_roader.h"

//-----------------------------
// @name   MenuScene
// @brief  メニューシーン
// @memo   セットしてから使うこと
//------------------------------

void MenuScene::PushCheck() {
	//直前の選択を保管
	last_select_ = selecter_;

	//W,Sキーで選択
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_--;
	}
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_++;
	}
	//セレクターをループさせる
	selecter_ = (selecter_ + k_menu_item_max) % k_menu_item_max;
	//選択位置の修正
	selecter_node_->SetPosition(line_set::selecter_x, line_set::selecter_y + selecter_ * line_set::brank_y * 2);
	//エンターで決定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		
		//セレクターの値で分ける
		switch (selecter_)
		{
		case k_play:
			next_scene_ = new SelectScene();
			break;
		case k_config:
			next_scene_ = new ConfigScene();
			break;
		case k_credit:
			next_scene_ = new CreditScene();
			break;
		default:
			next_scene_ = new ConfigScene();
			break;
		}

	}
	//Escキーで設定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_ESCAPE)) {
		MusicManager::GetInstance()->PlaySe(k_select);

		next_scene_ = new ConfigScene();
	}
}

void MenuScene::TextUpdate() {


	Node* new_text_ = new Node();
	new_text_->SetPosition(line_set::selecter_x + line_set::brank_x*3, line_set::selecter_y);

	//テキストデータ作成
	for (int i = 0; i < k_menu_item_max; i++) {
		
		std::string text = string_set::menu[i];
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		new_text_->AddChild(new TextNode(text.c_str(), GetColor(255, 255, 255),
			window_setting::null_param, line_set::brank_y * i * 2));

	}

	//元々根ノードがあるなら削除
	if (text_ != nullptr) {

		root_->DeleteChild(text_);

	}

	text_ = new_text_;
	root_->AddChild(new_text_);

}

void MenuScene::Init()
{
	//中身の設定
	root_ = new Node();
	camera_ = new Camera();
	int string_size = GetDrawStringWidth(string_set::select_menu, -1);

	selecter_node_ = new TextNode("->", GetColor(255, 255, 255), line_set::selecter_x, line_set::selecter_y);

	root_->AddChild(new TextNode(string_set::select_menu, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, line_set::midasi_y));
	root_->AddChild(selecter_node_);


	TextUpdate();



	//次のシーンをここに設定
	next_scene_ = this;
}

void MenuScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();

	//BGM再生
	MusicManager::GetInstance()->PlayBgm();
}

void MenuScene::Finalize()
{
	root_->ReleaseResourceAll();
	
}

Scene* MenuScene::Update(float delta_time)
{
	camera_->Update();

	//直前の選択が今の選択と違うならテキストを更新
	if (last_select_ != selecter_) {
		TextUpdate();
	}

	root_->UpdateAll(delta_time);

	root_->SetWorldPositionAll();

	MenuScene::PushCheck();


	return next_scene_;
}

void MenuScene::Draw(int screen_handle)
{
	root_->DrawAll(screen_handle, camera_);

}


//-----------------------------
// @name   SelectScene
// @brief  選択シーン
// @memo   セットしてから使うこと
//------------------------------

void SelectScene::PushCheck() {

	//直前の選択を保管
	last_select_ = selecter_;

	//W,Sキーで選択
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_--;
	}
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_++;
	}
	//セレクターをループさせる
	selecter_ = (selecter_ + MusicManager::GetInstance()->GetLineupSize()) % MusicManager::GetInstance()->GetLineupSize();
	//エンターで決定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		MusicManager::GetInstance()->SetPlayMusic(MusicManager::GetInstance()->operator[](selecter_).c_str());
		next_scene_ = new GameScene();
	}
	//Escキーで設定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_ESCAPE)) {
		MusicManager::GetInstance()->PlaySe(k_select);

		next_scene_ = new MenuScene();
	}

}

void SelectScene::TextUpdate()
{


	Node* new_text_ = new Node();
	new_text_->SetPosition(line_set::selecter_x, line_set::selecter_y);

	//テキストデータ作成
	for (int i = 0; i < line_set::amount_y_max; i++) {
		//表示番号の式　：　(選択している番号 - (表示上限の半分(偶数ずれ防止で-1)) + (ループ用の要素数) + 何列目に配置かの番号 - (実際の番号にするために-1)) % (ループ用の要素数)
		std::string text =
			MusicManager::GetInstance()->operator[]((selecter_ - ((line_set::amount_y_max - 1) / 2) + MusicManager::GetInstance()->GetLineupSize() + i) % MusicManager::GetInstance()->GetLineupSize());
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
	selecter_ = window_setting::null_param;

	root_->AddChild(new TextNode(string_set::select_song, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, line_set::midasi_y));
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

	//直前の選択が今の選択と違うならテキストを更新
	if (last_select_ != selecter_) {
		TextUpdate();
	}

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
