//-----------------------------
// @name   file_roader.cpp
// @brief  ファイル読み込み クラス
// @auther A.namami
// @date   2026/3/6  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <fstream>
#include <iostream>
#include "DxLib.h"

#include "..\130_data_manager\133_music\music_manager.h"
#include "..\130_data_manager\132_shots\shot_booker.h"
#include "..\110_drawing_tools\defining.h"
#include "file_roader.h"

FileRoader* FileRoader::roader_ = nullptr;

FileRoader::FileRoader()
{

}

FileRoader::~FileRoader()
{

}

FileRoader* FileRoader::GetInstance() {
	//インスタンスの確認
	if (roader_ == nullptr) {
		roader_ = new FileRoader();
	}
	return roader_;
}

void FileRoader::RoadLineup(std::vector<std::string>* title)
{
	//ポインタつくる
	std::ifstream lineup_p("..\\200_resource\\music\\Lineup.txt");

	if (lineup_p.is_open()) {
		std::string name;
		while (std::getline(lineup_p, name)) {
			title->push_back(name);
		}
	}
	
	lineup_p.close();
}

void FileRoader::RoadMusic(MusicData* music_data)
{
	//曲ハンドル
	std::string file_name = "..\\200_resource\\music\\" + music_data->title_ + "\\" + music_data->title_ + ".wav";

	music_data->handle_ = LoadSoundMem(file_name.c_str());
	std::cout << music_data->handle_ << std::endl;
	//プロパティ読み込み
	file_name = "..\\200_resource\\music\\" + music_data->title_ + "\\propaty.txt";
	std::ifstream propaty_p(file_name.c_str());
	if (propaty_p.is_open()) {
		propaty_p >> music_data->bpm_;
		propaty_p >> music_data->time_;
		propaty_p >> music_data->hyousi_;
	}

	propaty_p.close();
}

std::vector<ShotBooker>* FileRoader::RoadHumen(const MusicData& music_data)
{
	//ポインタつくる
	std::string file_name = "..\\200_resource\\music\\" + music_data.title_ + "\\humen.txt";
	std::ifstream humen_p(file_name.c_str());
	//譜面
	std::string humen_2;
	//デフォルト
	ShotBooker booked_def = { 8,system_set::shot_speed_def , 3,0, 1, false };
	
	//返り値
	std::vector<ShotBooker>* booker = new std::vector<ShotBooker>();

	//譜面あける
	if (humen_p.is_open()) {
		char pt;
		while (humen_p.get(pt)) {
			humen_2.push_back(pt);
		}
		humen_p.close();
	}

	//譜面変換する
	int retu = 0;//ファイルの列
	int setu = 0;//曲の節数
	int i = 0;//ループカウント
	while (humen_2.size() > i) {
		switch (humen_2[i])
		{
		case  '\0': break;
		case '\n':
			//タイミング調整をば

			//カウント調整

			for (int j = 0; j <= retu; j++) {
				ShotBooker booked = booked_def;//予約カード

				if (humen_2[i - retu + j] == '1') {
					float in_time = (float)(((setu + j / retu) + 1.0f) * music_data.hyousi_ * 60.0f  / music_data.bpm_); //時間

					booked.bool_time = in_time;
					booked.type = 0;
					booker->push_back(booked);
					
				}
			}
			setu++;
			retu = 0;
			

			break;

			//インクリメント
		default:

			retu++;
			break;
		}

		i++;

	}
	

	humen_p.close();

	return booker;
}
