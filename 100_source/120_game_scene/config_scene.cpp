//-----------------------------
// @name   config_scene.cpp
// @brief  設定シーン クラス
// @auther A.namami
// @date   2026/3/16  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "config_scene.h"
#include "../110_drawing_tools/node.h"
#include "../110_drawing_tools/text_node.h"
#include "../110_drawing_tools/inputer.h"
#include "../130_data_manager/134_other/configs_manager.h"
#include "../130_data_manager/133_music/music_manager.h"
#include "../130_data_manager/134_other/txt_font_manager.h"
#include "../140_roading_from_other/file_roader.h"

//-----------------------------
// @name   ConfigScene
// @brief  設定
// @memo   セットしてから使うこと
//------------------------------
void ConfigScene::PushCheck() {
	
	//直前の選択を保管
	last_select_ = selecter_;

	//W,Sで項目変更
	//Wなら上
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)) {
		selecter_--;
		MusicManager::GetInstance()->PlaySe(k_select);

	}
	//Sなら下
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S)) {
		selecter_++;
		MusicManager::GetInstance()->PlaySe(k_select);

	}
	//ループさせる
	selecter_ = (selecter_ + k_config_amount) % k_config_amount;
	//選択位置の修正
	selecter_node_->SetPosition(line_set::selecter_x, line_set::selecter_y + selecter_ * line_set::brank_y * 2);

	//A,Dで量調整
	//Aなら減少
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_A)) {
		ConfigsManager::GetInstance()->SubIt((Configs)selecter_);
		MusicManager::GetInstance()->PlaySe(k_select);

	}
	//Dなら増加
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_D)) {
		ConfigsManager::GetInstance()->AddIt((Configs)selecter_);
		MusicManager::GetInstance()->PlaySe(k_select);

	}

	//エンターで戻す
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		ConfigsManager::GetInstance()->SetIt();
		MusicManager::GetInstance()->PlaySe(k_select);

		next_scene_ = GetToReturnScene();
	}
	//エスケープキーで終了
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_ESCAPE)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		ConfigsManager::GetInstance()->SetEnd();
	}

}


void ConfigScene::TextUpdate()
{
	Node* new_text_ = new Node();
	new_text_->SetPosition(line_set::selecter_x, line_set::selecter_y);

	//テキストデータ作成
	for (int i = 0; i < k_config_amount; i++) {
		//まず曲音量
		std::string text = std::to_string(ConfigsManager::GetInstance()->GetIt((Configs)i));
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		new_text_->AddChild(new TextNode(text.c_str(), GetColor(255, 255, 255),
			line_set::brank_x * 3, line_set::brank_y * i * 2));

	}
	

	//元々根ノードがあるなら削除
	if (text_ != nullptr) {

		root_->DeleteChild(text_);

	}

	text_ = new_text_;
	root_->AddChild(new_text_);
}


void ConfigScene::Init()
{
	root_ = new Node();
	camera_ = new Camera();

	//中身の設定
	int string_size = GetDrawFormatStringWidthToHandle(TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1), string_set::config_set);

	selecter_node_ = new TextNode("->", GetColor(255, 255, 255), line_set::selecter_x, line_set::selecter_y);

	root_->AddChild(new TextFormatNode(string_set::config_set, GetColor(255, 255, 255), TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1), window_setting::center_x - string_size / 2, line_set::midasi_y));
	
	string_size = GetDrawStringWidth(string_set::push_to_return, -1);
	root_->AddChild(new TextNode(string_set::push_to_return, GetColor(255, 255, 255), window_setting::size_x - string_size - ege_set::brank_x, window_setting::size_y - line_set::brank_y * 3));
	
	root_->AddChild(new TextNode(string_set::push_to_end, GetColor(255, 255, 255), ege_set::brank_x, window_setting::size_y - line_set::brank_y * 3));
	
	//固定テキスト関係
	Node* new_text_ = new Node();
	new_text_->SetPosition(line_set::selecter_x, line_set::selecter_y);
	int string_size_max = NULL;
	//項目分追加
	for (int i = 0; i < k_config_amount; i++) {
		new_text_->AddChild(new TextNode(string_set::configs[i], GetColor(255, 255, 255), line_set::brank_x * 2, line_set::brank_y * (i * 2 - 1)));
		new_text_->AddChild(new TextNode("<", GetColor(255, 255, 255), line_set::brank_x * 2,  line_set::brank_y * i * 2));
		new_text_->AddChild(new TextNode(">", GetColor(255, 255, 255), line_set::brank_x * 5,  line_set::brank_y * i * 2));
	}
	root_->AddChild(new_text_);
	root_->AddChild(selecter_node_);


	//直前の選択が今の選択と違うならテキストを更新
	if (last_select_ != selecter_) {
		TextUpdate();
	}
	next_scene_ = this;
}



void ConfigScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();
}



void ConfigScene::Finalize()
{
	root_->ReleaseResourceAll();

}



Scene* ConfigScene::Update(float delta_time)
{
	TextUpdate();

	root_->UpdateAll(delta_time);

	root_->SetWorldPositionAll();

	ConfigScene::PushCheck();


	return next_scene_;
}



void ConfigScene::Draw(int screen_handle)
{
	root_->DrawAll(screen_handle, camera_);

}

//-----------------------------
// @name   CreditScene
// @brief  クレジット
// @memo   セットしてから使うこと
//------------------------------

void CreditScene::PushCheck() {
	//エンターで戻る
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		next_scene_ = GetToReturnScene();
	}
}

void CreditScene::Init()
{
	root_ = new Node();
	camera_ = new Camera();

	int string_size = GetDrawStringWidth(string_set::push_to_return, -1);
	root_->AddChild(new TextNode(string_set::push_to_return, GetColor(255, 255, 255), window_setting::size_x - string_size - ege_set::brank_x, window_setting::size_y - line_set::brank_y * 3));

	//テキストを設定
	FileRoader::GetInstance()->RoadSyutten(text_);

	root_->AddChild(new TextNode(text_.c_str(), GetColor(255, 255, 255), line_set::brank_x + ege_set::brank_x, line_set::brank_y + ege_set::brank_y));

	next_scene_ = this;
}

void CreditScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();
}

void CreditScene::Finalize()
{
	root_->ReleaseResourceAll();
}

Scene* CreditScene::Update(float delta_time)
{
	root_->UpdateAll(delta_time);

	root_->SetWorldPositionAll();

	CreditScene::PushCheck();

	return next_scene_;
}

void CreditScene::Draw(int screen_handle)
{
	root_->DrawAll(screen_handle, camera_);

}
