//-----------------------------
// @name   music_maker.h
// @brief  譜面ファイル作成 クラス
// @auther A.namami
// @date   2026/6/8  新規作成
//         2026/6/25 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <fstream>
#include "music_maker.h"
#include "read_music.h"
#include "data_manager.h"
#include "../../140_roading_from_other/file_roader.h"


bool MusicMaker::GetFile(std::string* name, WavData*& get_data, int* tag_rate, int* second_length)
{
	//mp3拡張子を調べる
	{
		std::string  names(*name);
		//MP3ファイル読込
		drmp3* file = nullptr;
		//ファイル存在の確認
		names.append(".mp3");
		if (drmp3_init_file(file, names.c_str(), NULL)) {

			get_data = ReadMp3::GetInstance()->ReadIt(file);
			*second_length = get_data->data_size / get_data->format.bytesPerSecond;//時間
			*tag_rate = get_data->format.samplePerSecond;//記録位置
			return true;
		}
	}

	//Wav拡張子を調べる
	{
		std::string  names(*name);
		//Wavファイル読み込み
		FILE* file = nullptr;
		//ファイル存在の確認
		names.append(".wav");
		fopen_s(&file, names.c_str(), "rb");

		if (file) {
			get_data = ReadWav::GetInstance()->ReadIt(file);
			*second_length = get_data->data_size / get_data->format.bytesPerSecond;
			*tag_rate = get_data->format.samplePerSecond;
			return true;
		}
	}
    return false;
}

bool MusicMaker::WriteFile(std::string* name, std::string* param)
{

	std::ofstream write_file(name->c_str());
	write_file.write(param->c_str(),param->size());
	write_file.close();

	return true;
}

bool MusicMaker::WritePropaty(std::string* name, MusicMakerWant* param, int second_length)
{

	return false;
}
