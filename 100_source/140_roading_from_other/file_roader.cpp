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

void FileRoader::RoadMusic(MusicData* music_data)
{
	//曲ハンドル
	std::string file_name = "..\\200_resource\\music\\" + music_data->title + "\\" + music_data->title + ".wav";

	music_data->handle = LoadSoundMem(file_name.c_str());
	std::cout << music_data->handle << std::endl;
	//プロパティ読み込み
	file_name = "..\\200_resource\\music\\" + music_data->title + "\\propaty.txt";
	std::ifstream propaty_p(file_name.c_str());
	if (propaty_p.is_open()) {
		propaty_p >> music_data->bpm;
		propaty_p >> music_data->time;
	}

}

std::vector<ShotBooker>* FileRoader::RoadHumen(const MusicData& music_data)
{
	//ポインタつくる
	std::string file_name = "..\\200_resource\\music\\" + music_data.title + "\\humen.txt";
	std::ifstream Humen_p(file_name.c_str());
	//譜面
	std::string Humen_2;
	//デフォルト
	ShotBooker booked_def = { 8, 10, 3,0, 1, false };
	ShotBooker booked = booked_def;
	//返り値
	std::vector<ShotBooker>* booker = new std::vector<ShotBooker>();

	//譜面あける
	if (Humen_p.is_open()) {
		char pt;
		while (Humen_p.get(pt)) {
			Humen_2.push_back(pt);
		}
	}

	//譜面変換する
	int retu = 0;
	int setu = 0;
	int i = 0;
	float last_time = 0.0f;
	while (Humen_2.size() > i) {
		switch (Humen_2[i])
		{
		case  '\0': break;
		case '\n':
			//タイミング調整をば

			//カウント調整

			for (int j = 0; j <= retu; j++) {
				booked = booked_def;

				if (Humen_2[i - retu + j] == '1') {
					double in_time = (((double)setu + (double)j / retu) + 1) * 4.0 * 60.0 / (double)music_data.bpm;

					booked.bool_time = in_time - last_time;
					booked.type = 0;
					booker->push_back(booked);
					last_time = booked.bool_time;
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
	

	Humen_p.close();

	return booker;
}
