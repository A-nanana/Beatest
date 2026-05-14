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

#include "../110_drawing_tools/text_node.h"
#include "../110_drawing_tools/line_node.h"
#include "../110_drawing_tools/inputer.h"
#include "../110_drawing_tools/tool.h"
#include "config_scene.h"
#include "background_node.h"
#include "../130_data_manager/133_music/music_manager.h"
#include "../130_data_manager/134_other/configs_manager.h"
#include "../130_data_manager/134_other/color_manager.h"
#include "../130_data_manager/134_other/txt_font_manager.h"
#include "../130_data_manager/134_other/window_manager.h"
#include "../140_roading_from_other/file_roader.h"

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
	selecter_node_->SetPosition(WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_ + selecter_ * line_set::brank_y * 2);
	selecter_node_->SetCenter();
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
		case k_about:
			next_scene_ = new AboutScene();
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
	new_text_->SetPosition(WindowManager::GetInstance()->GetSelecterCenter().x_ + line_set::brank_x, WindowManager::GetInstance()->GetSelecterCenter().y_);

	//テキストデータ作成
	for (int i = 0; i < k_menu_item_max; i++) {
		
		std::string text = string_set::menu[i];
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		new_text_->AddChild(new TextNode(text.c_str(), ColorManager::GetInstance()->SerchColor(string_set::font_nomal1),
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

	//メニュー画面の背景画像設定
	root_->AddChild(new BackgroundNode(file_set::menu_back_defalt, { window_setting::null_param,window_setting::null_param }));
	int string_size = GetDrawFormatStringWidthToHandle(TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1),string_set::select_menu);

	selecter_node_ = new GraphNode(file_set::selecter, WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_,window_setting::selecter_extender_,true);

	root_->AddChild(new TextFormatNode(string_set::select_menu, ColorManager::GetInstance()->SerchColor(string_set::font_midasi1), TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1), WindowManager::GetInstance()->GetWindowCenterX() - string_size / 2, line_set::midasi_y));
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
	last_select_[k_music] = selecter_[k_music];
	last_select_[k_defficult] = selecter_[k_defficult];
	int upper = 1; //難易度ループ用増加幅

	//W,Sキーで曲選択
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_W)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_[k_music]--;
	}
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_S)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_[k_music]++;
	}
	//A,Dキーで難易度選択
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_A)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_[k_defficult]--;
		upper = -1;
	}
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_D)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		selecter_[k_defficult]++;
		upper = +1;

	}
	//セレクターをループさせる
	selecter_[k_music] = (selecter_[k_music] + MusicManager::GetInstance()->GetLineupSize()) % MusicManager::GetInstance()->GetLineupSize();
	//難易度に関しても同じ
	for (int i = 0; i < system_set::defficulter_max; i++) {
		//その難易度が存在するか
		if (((1 << selecter_[k_defficult] ) & (MusicManager::GetInstance()->operator[](selecter_[k_music]).defficalt_flg_))) {
			break;
		}
		//そうでなければセレクターを次に
		selecter_[k_defficult] += upper;

		selecter_[k_defficult] = (selecter_[k_defficult] + system_set::defficulter_max) % system_set::defficulter_max;

	}
	

	//エンターで決定
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		MusicManager::GetInstance()->PlaySe(k_select);
		MusicManager::GetInstance()->SetPlayMusic(MusicManager::GetInstance()->operator[](selecter_[k_music]));
		MusicManager::GetInstance()->SetDefficult(selecter_[k_defficult]);
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
	new_text_->SetPosition(WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_);

	//テキストデータ作成
	for (int i = 0; i < line_set::amount_y_max; i++) {
		//表示番号の式　：　(選択している番号 - (表示上限の半分(偶数ずれ防止で-1)) + (ループ用の要素数) + 何列目に配置かの番号 - (実際の番号にするために-1)) % (ループ用の要素数)
		std::string text =
			MusicManager::GetInstance()->operator[]((selecter_[k_music] - ((line_set::amount_y_max - 1) / 2) + MusicManager::GetInstance()->GetLineupSize() + i) % MusicManager::GetInstance()->GetLineupSize()).title;
		int string_size = GetDrawStringWidth(text.c_str(), -1);

		new_text_->AddChild(new TextNode(text.c_str(), ColorManager::GetInstance()->SerchColor(string_set::font_nomal1),
			line_set::brank_x, line_set::brank_y * i));

	}
	//ハイスコアの表示
	new_text_->AddChild(new TextNode(std::to_string(MusicManager::GetInstance()->operator[](selecter_[k_music]).high_score[selecter_[k_defficult]].value_or(window_setting::null_param)).c_str(), ColorManager::GetInstance()->SerchColor(string_set::font_nomal1),
		WindowManager::GetInstance()->GetWindowCenterX(), line_set::brank_y * (line_set::amount_y_max - 1)));

	//元々根ノードがあるなら削除
	if (text_ != nullptr) {

		root_->DeleteChild(text_);

	}

	text_ = new_text_;
	root_->AddChild(new_text_);

}

SelectScene::SelectScene()
	:text_(nullptr) {
	root_ = new Node();
	camera_ = new Camera();
	selecter_[k_music] = NULL; selecter_[k_defficult] = NULL;
	last_select_[k_music] = NULL; last_select_[k_defficult] = NULL;
	next_scene_ = nullptr;

	//ポインタ初期化
	for (int i = 0; i < system_set::defficulter_max; i++) {
		
		defficult_[i] = nullptr;
		
	}
}
void SelectScene::Init() {
	MusicManager::GetInstance()->SetLineUp();

	root_->AddChild(new BackgroundNode(file_set::menu_back_defalt, { window_setting::null_param,window_setting::null_param }));

	int string_size = GetDrawFormatStringWidthToHandle(TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1), string_set::select_song);

	GraphNode* check_size = new GraphNode(file_set::selecter, WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_ + line_set::brank_y * 2, window_setting::selecter_extender_, true);
	//サイズ設定のためにロード
	check_size->Load();

	//固定UIオブジェクト追加
	root_->AddChild(new TextFormatNode(string_set::select_song, ColorManager::GetInstance()->SerchColor(string_set::font_midasi1), TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi1), WindowManager::GetInstance()->GetWindowCenterX() - string_size / ((line_set::amount_y_max - 1) / 2), line_set::midasi_y));
	root_->AddChild(new TextNode(string_set::high_score, ColorManager::GetInstance()->SerchColor(string_set::font_midasi2), WindowManager::GetInstance()->GetWindowCenterX() + WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_ + line_set::brank_y * (line_set::amount_y_max - 2)));
	//スコア更新が出来ないならその旨の文を追加
	if (!FileRoader::GetInstance()->CanUseDb()){
		string_size = GetDrawFormatStringWidth(string_set::cannot_update);
		root_->AddChild(new TextNode(string_set::cannot_update, ColorManager::GetInstance()->SerchColor(string_set::font_secure), WindowManager::GetInstance()->GetWindowSize().x_ - string_size - line_set::brank_x,
			WindowManager::GetInstance()->GetSelecterCenter().y_ + line_set::brank_y * (line_set::amount_y_max - 3)));
	}
	root_->AddChild(check_size);
	root_->AddChild(new LineNode(WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetSelecterCenter().y_ + line_set::brank_y * 2 + check_size->GetSizeY() /2, WindowManager::GetInstance()->GetWindowCenterX() - WindowManager::GetInstance()->GetSelecterCenter().x_, 0.0f,GetColor(0,0,0),1.0f));
	
	//	難易度
	for (int i = 0; i < system_set::defficulter_max; i++) {
		defficult_[i] = new TextNode(string_set::defficult[i], ColorManager::GetInstance()->SerchColor(string_set::font_midasi2), WindowManager::GetInstance()->GetSelecterCenter().x_, WindowManager::GetInstance()->GetWindowCenterY() + WindowManager::GetInstance()->GetSelecterCenter().y_ - line_set::brank_y);
	}
	//位置初期化
	for (int i = 0; i < system_set::defficulter_max; i++) {
		//存在するか
		if (defficult_[i] != nullptr) {
			defficult_[i]->SetWorldPositionAll();
		}
	}

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
	defficult_[selecter_[k_defficult]]->DrawAll(screen_handle, camera_);
}

void SelectScene::Finalize() {
	root_->ReleaseResourceAll();
	
}
