//-----------------------------
// @name   tutorial_scene.cpp
// @brief  チュートリアル クラス
// @auther A.namami
// @date   2026/9/1  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "../140_roading_from_other/file_roader.h"
#include "../130_data_manager/134_other/txt_font_manager.h"
#include "../130_data_manager/133_music/music_manager.h"
#include "result_scene.h"
#include "tutorial_scene.h"
#include "menu_scene.h"

void TutorialScene::UpdateTxt()
{
	if ((last_pop_up_ + 2 * system_set::ms_per_s < last_time_) ) //テキスト消去
	{
		tutorial_txt_->SetText("");
		last_pop_up_ = last_time_;
		return;
	}
	if (text_all_.GetCsv()->empty()) {
		return;
	}
	//テキスト更新
	if (text_all_.GetCsv()->front().time * system_set::ms_per_s <= last_time_) {

		tutorial_txt_->SetText(text_all_.GetCsv()->front().text.c_str());
		//最初を削除
		text_all_.DelFront();
		last_pop_up_ = last_time_;

	}
	
}

void TutorialScene::Init() {
	
	MusicManager::GetInstance()->SetPlayMusic({ "tutorial",{0,0,0,0}, 0,0});
	MusicManager::GetInstance()->SetDefficult(0);
	//テキスト設定
	std::string txt("0,Hello,");//入力テキスト
	FileRoader::GetInstance()->RoadTxt(txt,"200_resource/testcsv.csv");
	text_all_.ConvertCsv(txt.c_str());
	//ゲームシーン側初期化
	GameScene::Init();
	tutorial_txt_ = new TextNode("test",255,255,255,10,10);

}

void TutorialScene::SetUp()
{
	//テキスト準備
	tutorial_txt_->LoadResourceAll();
	UpdateTxt();
	//ゲームシーン側セットアップ
	GameScene::SetUp();
}

void TutorialScene::Finalize()
{
	tutorial_txt_->ReleaseResourceAll();

	//ゲームシーン側ファイナライズ
	GameScene::Finalize();

}

Scene* TutorialScene::Update(float delta_time)
{
	//ゲームシーン側更新
	GameScene::Update(delta_time);

	//テキスト更新
	
	UpdateTxt();


	if (next_scene_ != this) {
		ResultScene* casting_scene = dynamic_cast<ResultScene*>(next_scene_);
		if (casting_scene) {
			casting_scene->Finalize();
			next_scene_ = new MenuScene();
		}

	}
	return next_scene_;
}

void TutorialScene::Draw(int screen_handle)
{
	//ゲームシーン側描画
	GameScene::Draw(screen_handle);

	//チュートリアル文の描画
	tutorial_txt_->Draw(screen_handle,camera_);

	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", last_time_);
	DrawFormatString(120,120, GetColor(255,255,255),"%d",last_pop_up_);

}

//Csv関係

void TutorialCsv::ConvertCsv(const char* csv)
{
	int size = 0;
	{
		std::string csv_char(csv);
		size = csv_char.size();
	}
	int i = 0; //カウント(文字)
	int check = 0;//最終確認位置
	CsvLavel lavel = k_csv_time; //Csv項目
	CsvData pool_data; //初期データ
	std::string text_moto;//変換前テキスト

	while (true)
	{
		if (csv[i] != '\r') {
			text_moto.push_back(csv[i]);
		}
		//区切りなら分岐
		if (csv[i] == ',' || csv[i] == '\n') {

			//ラベルで変換
			switch (lavel)
			{
			case k_csv_time:

				pool_data.time = std::stoi(text_moto);
				
				check = i;
				lavel = k_csv_text;
				break;
			case k_csv_text:

				pool_data.text = text_moto;

				check = i;
				lavel = k_csv_time;
				break;
			}
			text_moto.clear();

		}
		//改行で代入
		if (csv[i] == '\n') {
			

			csv_data_.push_back(pool_data);
		}
		++i;

		//最後ならそこで終了
		if (size <= i) {
			break;
		}

	}
}

void TutorialCsv::DelFront()
{
	csv_data_.pop_front();
}
