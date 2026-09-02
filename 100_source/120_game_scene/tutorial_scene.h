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

#include <list>

#include "game_scene.h"
#include "../110_drawing_tools/text_node.h"



//チュートリアルテキスト用CSVファイル
//Csvデータチャンク
struct CsvData
{
	std::string text;//テキスト
	int time;//時間
};
//実際のデータ
//データの並び
enum CsvLavel {
	k_csv_time, //時間
	k_csv_text, //テキスト

	k_csv_max
};

class TutorialCsv {
protected:
	std::list<CsvData> csv_data_; //Csvのリスト
public:
	void ConvertCsv(const char* csv);//コンバーター
	const std::list<CsvData>* GetCsv() { return &csv_data_; } //Csvの取得
	void DelFront();//先頭除去

};

//チュートリアルシーンクラス
class TutorialScene: public GameScene
{
protected:
	TextNode* tutorial_txt_; //チュートリアル表示文
	TutorialCsv text_all_;
	const int text_pop_time_ = 3000;//テキスト表示時間

	int last_pop_up_ = 0;//テキスト表示開始時間

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

