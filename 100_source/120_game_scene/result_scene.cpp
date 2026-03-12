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
#include "top_scene.h"
#include "..\110_drawing_tools\buttom_node.h"
#include "..\110_drawing_tools\text_node.h"
#include "..\110_drawing_tools\game_scene.h"
#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\134_other\score_manager.h"
#include "..\140_roading_from_other\file_roader.h"
#include "..\110_drawing_tools\inputer.h"
#include "..\110_drawing_tools\defining.h"

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
		fase_ = k_fase_end_;
		time_hold_ = NULL;
		break;
	case k_fase_end_:
		//待機時間を満たしたか
		if (time_hold_ > system_set::need_wait_time_) {
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
	int string_size = GetDrawStringWidth(string_set::result, -1);

	Node* ko2 = new TextNode(string_set::result, GetColor(255, 255, 255), window_setting::center_x - string_size / 2, line_set::midasi_y);

	root_->AddChild(ko2);
	root_->AddChild(new TextNode(string_set::score, GetColor(255, 255, 255), window_setting::center_x / 2 - line_set::brank_x, line_set::midasi_y + line_set::selecter_y));
	root_->AddChild(new TextNode(string_set::max_conbo, GetColor(255, 255, 255), window_setting::center_x / 2 - line_set::brank_x, line_set::midasi_y + line_set::selecter_y + line_set::brank_y));

	//ここからフェーズ切り替え用
	root_res_[k_fase_all_res_] = new TextNode(ScoreManager::GetInstance()->GetScore().c_str(), GetColor(255, 255, 255),
		window_setting::center_x , line_set::midasi_y + line_set::selecter_y);
	root_res_[k_fase_conbo_] = new TextNode(ScoreManager::GetInstance()->GetMaxConbo().c_str(), GetColor(255, 255, 255),
		window_setting::center_x , line_set::midasi_y + line_set::selecter_y + line_set::brank_y);


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