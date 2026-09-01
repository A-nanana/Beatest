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
#include "../130_data_manager/133_music/music_manager.h"
#include "tutorial_scene.h"

void TutorialScene::UpdateTxt()
{
	//テキスト更新
	if (!text_all_.GetCsv()->empty()) {
		tutorial_txt_->SetText(text_all_.GetCsv()->front().text.c_str());
		//再読み込み
		tutorial_txt_->LoadResourceAll();
		tutorial_txt_->SetUpAll();

		//最初を削除
		text_all_.GetCsv()->erase(text_all_.GetCsv()->begin());
	}
}

void TutorialScene::Init() {
	
	MusicManager::GetInstance()->SetPlayMusic({ "tutorial",{0,0,0,0}, });
	MusicManager::GetInstance()->SetDefficult();
	//テキスト設定
	std::string txt;//入力テキスト
	FileRoader::GetInstance()->RoadTxt(txt,"testcsv.csv");
	text_all_.ConvertCsv(txt.c_str());
	//ゲームシーン側初期化
	GameScene::Init();

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
	if (text_all_.GetCsv()->front().time >= last_pop_up_) {
		UpdateTxt();
		last_pop_up_ = last_time_;
	}

	return next_scene_;
}

void TutorialScene::Draw(int screen_handle)
{
	//ゲームシーン側描画
	GameScene::Draw(screen_handle);

	//チュートリアル文の描画
	tutorial_txt_->Draw(screen_handle,camera_);

}

//Csv関係

void TutorialCsv::ConvertCsv(const char* csv)
{
	std::string csv_char(csv);
	int i = 0; //カウント(文字)
	int check = 0;//最終確認位置
	CsvLavel lavel = k_csv_time; //Csv項目
	CsvData pool_data = { "test",0}; //初期データ
	std::string text_moto;//変換前テキスト

	while (true)
	{
		//区切りなら分岐
		if (csv_char[i] == ',' || csv_char[i] == '\n') {

			text_moto = std::string(csv_char[check], csv_char[i - 1]);

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
			default:
			}
			

		}
		//改行で代入
		if (csv_char[i] == '\n') {
			csv_data_.push_back(pool_data);
		}
		++i;

		//最後ならそこで終了
		if (csv_char.size() >= i) {
			break;
		}

	}
}
