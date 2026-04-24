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
#include "menu_scene.h"

#include "../110_drawing_tools/graph_node.h"
#include "../110_drawing_tools/text_node.h"
#include "../110_drawing_tools/inputer.h"
#include "../110_drawing_tools/defining.h"
#include "../120_game_scene/config_scene.h"
#include "../130_data_manager/133_music/music_manager.h"
#include "../130_data_manager/134_other/configs_manager.h"
#include "../130_data_manager/134_other/window_manager.h"
#include "../140_roading_from_other/file_roader.h"

//-----------------------------
// @name   TopScene
// @brief  表紙
// @memo   セットしてから使うこと
//------------------------------

void TopScene::PushCheck() {
	//エンターキーが押されたら遷移
	if (Inputer::GetInstance()->GetDownKey(KEY_INPUT_RETURN)) {
		next_scene_ = new MenuScene();
	}
}


void TopScene::Init()
{
	//データ設定
	ConfigsManager::GetInstance()->SetIt();
	//中身作成
	root_ = new Node();
	camera_ = new Camera();

	//タイトル
	GraphNode* nodes = new GraphNode(file_set::title_top, WindowManager::GetInstance()->GetWindowCenterX(), line_set::title_y,true);

	root_->AddChild(nodes);
	
	int string_size = GetDrawStringWidth(string_set::push_to_start, -1);

	root_->AddChild(new TextNode(string_set::push_to_start, GetColor(255, 255, 255), WindowManager::GetInstance()->GetWindowCenterX() - string_size / 2, line_set::push_txt_y));
	


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


