//-----------------------------
// @name   file_manager.h
// @brief  譜面ファイル作成 クラス
// @auther A.namami
// @date   2026/6/8  新規作成
//         2026/6/25 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include <fstream>
#include "file_manager.h"
#include "read_music.h"


bool FileManager::GetFile(std::string* name, WavData* &get_data,int* tag_rate,int* second_length)
{
    //見つかった拡張子によって変える
    if (name->find(".mp3")) {
		//MP3ファイル読込
		drmp3* file = nullptr;
		//ファイルなしで終了
		if (!drmp3_init_file(file, name->c_str(), NULL)) {
			return false;
		}
		get_data = ReadMp3::GetInstance()->ReadIt(file);
		*second_length = get_data->data_size / get_data->format.bytesPerSecond;//時間
		*tag_rate = get_data->format.samplePerSecond;//記録位置
		return true;
    }
	if (name->find(".wav")) {
		//Wavファイル読み込み
		FILE* file = nullptr;
		fopen_s(&file, name->c_str(), "rb");
		//ファイルなしで終了
		if (!file) {
			return false;
		}

		get_data = ReadWav::GetInstance()->ReadIt(file);
		*second_length = get_data->data_size / get_data->format.bytesPerSecond;
		*tag_rate = get_data->format.samplePerSecond;
		return true;
	}

    return false;
}

bool FileManager::WriteFile(std::string* name, std::string* param)
{

	std::ofstream write_file(name->c_str());
	write_file.write(param->c_str(),param->size());
	write_file.close();

	return true;
}
