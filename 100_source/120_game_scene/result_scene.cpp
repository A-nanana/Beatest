//-----------------------------
// @name   result_scene.cpp
// @brief  結果シーン クラス
// @auther A.namami
// @date   2026/3/10  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include <iostream>
#include "result_scene.h"
#include "menu_scene.h"
#include "..\110_drawing_tools\buttom_node.h"
#include "..\110_drawing_tools\text_node.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\110_drawing_tools\defining.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\134_other\score_manager.h"
#include "..\130_data_manager\134_other\txt_font_manager.h"
#include "..\140_roading_from_other\file_roader.h"

//-----------------------------
// @name   ResultScene
// @brief  結果
// @memo   セットしてから使うこと
//------------------------------

//  コンストラクタ
ResultScene::ResultScene()
{
}

//キーの押し確認
void ResultScene::PushCheck() {
	
	//押されなくても切り替える
	//待機時間を満たした+終了判定ではないか
	if ((time_hold_ > effect_param::wait_score) && fase_ != k_fase_end_) {
		//状態で処理切り替え
		switch (fase_) {
		case k_fase_critical_:
			fase_ = k_fase_great_;
			break;
		case k_fase_great_:
			fase_ = k_fase_good_;
			break;
		case k_fase_good_:
			fase_ = k_fase_miss_;
			break;
		case k_fase_miss_:
			fase_ = k_fase_end_;
		}
		time_hold_ = NULL;

	}
	//エンターで決定
	if (!Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {

		return;
	}
	//状態で処理切り替え
	switch (fase_) {
	case k_fase_all_res_:
		fase_ = k_fase_conbo_;
		break;
	case k_fase_conbo_:
		fase_ = k_fase_critical_;
		time_hold_ = NULL;
		break;
	case k_fase_end_:
		//待機時間を満たしたか
		if (time_hold_ > system_set::need_wait_time_) {
			MusicManager::GetInstance()->PlaySe(k_select);
			next_scene_ = new SelectScene();
		}
	}

}
//テキストデータのアップデート
void ResultScene::TextUpdate() {
	//そもそも終了か
	if (fase_ == k_fase_end_) { return; }

	//結果のノードが存在しないか
	if (root_res_[fase_] == nullptr) {
		return;
	}
	
	//あるならルートノードに移す
	root_->AddChild(root_res_[fase_]);
	root_res_[fase_] = nullptr;

}

//  初期化
void ResultScene::Init() {

	root_ = new Node();
	camera_ = new Camera();
	int string_size = GetDrawFormatStringWidthToHandle(TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi2), string_set::result);


	root_->AddChild(new TextFormatNode(string_set::result, GetColor(255, 255, 255), TxtFontManager::GetInstance()->SerchFont(string_set::font_midasi2),window_setting::center_x - string_size / 2, line_set::midasi_y));
	root_->AddChild(new TextNode(string_set::score, GetColor(255, 255, 255), window_setting::center_x / 2 - line_set::brank_x, line_set::reslt_y + line_set::selecter_y));
	root_->AddChild(new TextNode(string_set::max_conbo, GetColor(255, 255, 255), window_setting::center_x / 2 - line_set::brank_x, line_set::reslt_y + line_set::selecter_y + line_set::brank_y));

	//ここからフェーズ切り替え用
	//最終結果
	root_res_[k_fase_all_res_] = new TextNode(ScoreManager::GetInstance()->GetScore().c_str(), GetColor(255, 255, 255),
		window_setting::center_x , line_set::reslt_y + line_set::selecter_y);

	//最大コンボ
	root_res_[k_fase_conbo_] = new TextNode(ScoreManager::GetInstance()->GetMaxConbo().c_str(), GetColor(255, 255, 255),
		window_setting::center_x , line_set::reslt_y + line_set::selecter_y + line_set::brank_y);

	//コンボ内訳
	root_res_[k_fase_critical_] = new TextNode(ScoreManager::GetInstance()->GetCritical().c_str(), GetColor(255, 255, 255),
		window_setting::center_x, line_set::reslt_y + line_set::selecter_y + line_set::brank_y * 2);
	root_res_[k_fase_critical_]->AddChild(new TextNode(string_set::result_uchiwake[k_critical], GetColor(255, 255, 255),
		-string_size, window_setting::null_param));

	root_res_[k_fase_great_] = new TextNode(ScoreManager::GetInstance()->GetGreat().c_str(), GetColor(255, 255, 255),
		window_setting::center_x, line_set::reslt_y + line_set::selecter_y + line_set::brank_y * 3);
	root_res_[k_fase_great_]->AddChild(new TextNode(string_set::result_uchiwake[k_great], GetColor(255, 255, 255),
		-string_size, window_setting::null_param));

	root_res_[k_fase_good_] = new TextNode(ScoreManager::GetInstance()->GetGood().c_str(), GetColor(255, 255, 255),
		window_setting::center_x, line_set::reslt_y + line_set::selecter_y + line_set::brank_y * 4);
	root_res_[k_fase_good_]->AddChild(new TextNode(string_set::result_uchiwake[k_none], GetColor(255, 255, 255),
		-string_size, window_setting::null_param));

	root_res_[k_fase_miss_] = new TextNode(ScoreManager::GetInstance()->GetMiss().c_str(), GetColor(255, 255, 255),
		window_setting::center_x, line_set::reslt_y + line_set::selecter_y + line_set::brank_y * 5);
	root_res_[k_fase_miss_]->AddChild(new TextNode(string_set::result_uchiwake[k_miss], GetColor(255, 255, 255),
		-string_size, window_setting::null_param));
	string_size = GetDrawStringWidth(string_set::push_to_return, -1);
	root_res_[k_fase_miss_]->AddChild(new TextNode(string_set::push_to_return, GetColor(255, 255, 255), window_setting::size_x - string_size - ege_set::brank_x, window_setting::size_y - line_set::brank_y * 3));


	next_scene_ = this;
}
//  準備
void ResultScene::SetUp() {
	root_->LoadResourceAll();
	root_->SetUpAll();
	
}
//  終了
void ResultScene::Finalize() {
	root_->ReleaseResourceAll();
	ScoreManager::GetInstance()->Reset();
	//BGM再生
	MusicManager::GetInstance()->PlayBgm();
}
//  更新
Scene* ResultScene::Update(float delta_time) {
	camera_->Update();
	
	TextUpdate();

	root_->UpdateAll(delta_time);
	root_->SetWorldPositionAll();
	//時間加算
	time_hold_ += delta_time;
	
	PushCheck();

	return next_scene_;
}
//  描画
void ResultScene::Draw(int screen_handle) {
	root_->DrawAll(screen_handle, camera_);

}