//-----------------------------
// @name   tutorial_scene.h
// @brief  チュートリアル クラスの宣言部
// @auther A.namami
// @date   2026/9/1  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once

#include "game_scene.h"
#include "../110_drawing_tools/text_node.h"

class TutorialScene:GameScene
{
protected:
	TextNode* tutorial_txt_; //チュートリアル表示文

public:
	//テキスト更新
	void UpdateTxt();

	//  初期化
	void Init() override;
	//  準備
	void SetUp() override;
	//  終了
	void Finalize() override;
	//  更新
	Scene* Update(float delta_time) override;
	//  描画
	void Draw(int screen_handle) override;

};

