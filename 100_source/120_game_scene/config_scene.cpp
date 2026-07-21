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

#include "background_node.h"
#include "../110_drawing_tools/node.h"
#include "../110_drawing_tools/text_node.h"
#include "../110_drawing_tools/inputer.h"
#include "../130_data_manager/134_other/configs_manager.h"
#include "../130_data_manager/133_music/music_manager.h"
#include "../130_data_manager/134_other/color_manager.h"
#include "../130_data_manager/134_other/txt_font_manager.h"
#include "../130_data_manager/134_other/window_manager.h"
#include "../140_roading_from_other/file_roader.h"

//-----------------------------
// @name   ConfigScene
// @brief  設定
// @memo   セットしてから使うこと
//------------------------------
void ConfigScene::PushCheck() {
	
	//直前の選択を保管
	last_select_ = selecter_;
	int pad_log = 0;//フラグでパッドの方向管理
	/*
	* 1ビット目　上 2ビット目　下
	* 3ビット目　右 4ビット目　左
	*/
	{
		float pad_x = 0, pad_y = 0;
		Inputer::GetInstance()->GetStickAmount(&pad_x, &pad_y);
		//パッドの上判定
		if ((Inputer::GetInstance()->GetDownPad(PAD_INPUT_UP) || pad_y > 0) && Inputer::GetInstance()->GetIsPad()) {
			pad_log |= 1 << 0;
		}
		//パッドの下判定
		if ((Inputer::GetInstance()->GetDownPad(PAD_INPUT_DOWN) || pad_y < 0) && Inputer::GetInstance()->GetIsPad()) {
			pad_log |= 1 << 1;
		}
		//パッドの右判定
		if ((Inputer::GetInstance()->GetDownPad(PAD_INPUT_RIGHT) || pad_x < 0) && Inputer::GetInstance()->GetIsPad()) {
			pad_log |= 1 << 2;
		}
		//パッドの左判定
		if ((Inputer::GetInstance()->GetDownPad(PAD_INPUT_LEFT) || pad_x > 0) && Inputer::GetInstance()->GetIsPad()) {
			pad_log |= 1 << 3;
		}
	}
	//W,Sで項目変更
	//Wなら上
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)|| (pad_log & 1 << 0) != 0) {
		selecter_--;
		MusicManager::GetInstance()->PlaySe(k_select);

	}
	//Sなら下
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S) || (pad_log & 1 << 1) != 0) {
		selecter_++;
		MusicManager::GetInstance()->PlaySe(k_select);

	}
	//ループさせる
	selecter_ = (selecter_ + k_config_amount) % k_config_amount;
	//選択位置の修正
	selecter_node_->SetPosition(WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_ + selecter_ * line_set::brank_y * 2);
	selecter_node_->SetCenter();

	//A,Dで量調整
	//Aなら減少
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_A) || (pad_log & 1 << 2) != 0) {
		ConfigsManager::GetInstance()->SubIt((Configs)selecter_);
		MusicManager::GetInstance()->PlaySe(k_select);

	}
	//Dなら増加
	if (Inputer::GetInstance()->GetHitKey(KEY_INPUT_D) || (pad_log & 1 << 3) != 0) {
		ConfigsManager::GetInstance()->AddIt((Configs)selecter_);
		MusicManager::GetInstance()->PlaySe(k_select);

	}

	//エンターで戻す
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN) || (Inputer::GetInstance()->GetDownPad(PAD_INPUT_2) && Inputer::GetInstance()->GetIsPad())) {
		ConfigsManager::GetInstance()->SetIt();
		MusicManager::GetInstance()->PlaySe(k_select);

		next_scene_ = GetToReturnScene();
	}
	//エスケープキーで終了
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_ESCAPE) || (Inputer::GetInstance()->GetDownPad(PAD_INPUT_1) || Inputer::GetInstance()->GetDownPad(PAD_INPUT_7))) {
		MusicManager::GetInstance()->PlaySe(k_select);
		ConfigsManager::GetInstance()->SetEnd();
	}

}


void ConfigScene::TextUpdate()
{
	Node* new_text_ = new Node();
	new_text_->SetPosition(WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_);

	//テキストデータ作成
	for (int i = 0; i < k_config_amount; i++) {
		//まず曲音量
		std::string text = std::to_string(ConfigsManager::GetInstance()->GetIt((Configs)i));
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		new_text_->AddChild(new TextNode(text.c_str(),ColorManager::GetInstance()->SerchColor(string_set::font_nomal1),
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
	root_->AddChild(new BackgroundNode(file_set::menu_back_defalt, { window_setting::null_param,window_setting::null_param }));

	selecter_node_ = new GraphNode(file_set::selecter, WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_, window_setting::selecter_extender_, true);

	root_->AddChild(new TextFormatNode(string_set::config_set,ColorManager::GetInstance()->SerchColor(string_set::font_midasi1), TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1), WindowManager::GetInstance()->GetWindowCenterX() - string_size / 2, line_set::midasi_y));
	
	string_size = GetDrawStringWidth(string_set::push_to_return, -1);
	root_->AddChild(new TextNode(string_set::push_to_return,ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), WindowManager::GetInstance()->GetWindowSize().x_ - string_size - ege_set::brank_x, WindowManager::GetInstance()->GetWindowSize().y_ - line_set::brank_y ));
	
	root_->AddChild(new TextNode(string_set::push_to_end,ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), ege_set::brank_x, WindowManager::GetInstance()->GetWindowSize().y_ - line_set::brank_y ));
	
	//固定テキスト関係
	Node* new_text_ = new Node();
	new_text_->SetPosition(WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_);
	int string_size_max = NULL;
	//項目分追加
	for (int i = 0; i < k_config_amount; i++) {
		new_text_->AddChild(new TextNode(string_set::configs[i],ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x * 2, line_set::brank_y * (i * 2 - 1)));
		new_text_->AddChild(new TextNode("<",ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x * 2,  line_set::brank_y * i * 2));
		new_text_->AddChild(new TextNode(">",ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x * 5,  line_set::brank_y * i * 2));
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
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN) || (Inputer::GetInstance()->GetDownPad(PAD_INPUT_2) && Inputer::GetInstance()->GetIsPad())) {
		next_scene_ = GetToReturnScene();
	}
}

void CreditScene::Init()
{
	root_ = new Node();
	camera_ = new Camera();
	root_->AddChild(new BackgroundNode(file_set::menu_back_defalt, { window_setting::null_param,window_setting::null_param }));

	int string_size = GetDrawStringWidth(string_set::push_to_return, -1);
	root_->AddChild(new TextNode(string_set::push_to_return,ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), WindowManager::GetInstance()->GetWindowSize().x_ - string_size - ege_set::brank_x, WindowManager::GetInstance()->GetWindowSize().y_ - line_set::brank_y * 3));

	//テキストを設定
	FileRoader::GetInstance()->RoadTxt(text_,file_set::syutten_memo);

	root_->AddChild(new TextNode(text_.c_str(),ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x + ege_set::brank_x, line_set::brank_y + ege_set::brank_y));

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


//-----------------------------
// @name   AboutScene
// @brief  説明
// @memo   セットしてから使うこと
//------------------------------
void AboutScene::PushCheck() {
	//エンターで戻る
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN) || (Inputer::GetInstance()->GetDownPad(PAD_INPUT_2) && Inputer::GetInstance()->GetIsPad())) {
		next_scene_ = GetToReturnScene();
	}
}

void AboutScene::Init()
{
	root_ = new Node();
	camera_ = new Camera();
	root_->AddChild(new BackgroundNode(file_set::menu_back_defalt, { window_setting::null_param,window_setting::null_param }));

	int string_size = GetDrawStringWidth(string_set::push_to_return, -1);
	root_->AddChild(new TextNode(string_set::push_to_return,ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), WindowManager::GetInstance()->GetWindowSize().x_ - string_size - ege_set::brank_x, WindowManager::GetInstance()->GetWindowSize().y_ - line_set::brank_y * 3));

	//テキストを設定
	FileRoader::GetInstance()->RoadTxt(text_, file_set::tutorial_memo);

	root_->AddChild(new TextNode(text_.c_str(),ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x + ege_set::brank_x, line_set::brank_y + ege_set::brank_y));

	next_scene_ = this;
}

void AboutScene::SetUp()
{
	root_->LoadResourceAll();
	root_->SetUpAll();
}

void AboutScene::Finalize()
{
	root_->ReleaseResourceAll();
}

Scene* AboutScene::Update(float delta_time)
{
	root_->UpdateAll(delta_time);

	root_->SetWorldPositionAll();

	AboutScene::PushCheck();

	return next_scene_;
}

void AboutScene::Draw(int screen_handle)
{
	root_->DrawAll(screen_handle, camera_);

}
