//-----------------------------
// @name   data_manager.cpp
// @brief  共有データ管理 クラス
// @auther A.namami
// @date   2026/6/11  新規作成
//         2026/6/15  取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "data_manager.h"

void DataManager::Mutex()
{
	std::lock_guard<std::mutex> lock_(mtx_);
}

Maker DataManager::GetMaker()
{
	Mutex();
	return *maker_;
}

WavData DataManager::GetWav()
{
	Mutex();
	return *wav_data_;
}

MusicData DataManager::GetMusicData()
{
	Mutex();
	return *music_data_;
}

int DataManager::GetTagTimr()
{
	Mutex();
	return tag_time_;
}

int DataManager::GetTime()
{
	Mutex();
	return time_;
}

bool DataManager::GetFinRead()
{
	Mutex();
	return is_fin_read_;
}

bool DataManager::GetFinWrite()
{
	Mutex();
	return is_fin_write_;
}

bool DataManager::GetEnd()
{
	Mutex();
	return is_end_;
}

std::string DataManager::GetTitle()
{
	Mutex();
	return title_;
}

int DataManager::SetTagTime(int tag_time) {
	Mutex();
	tag_time_ = tag_time;
	return tag_time_; 
}

int DataManager::SetTime(int tm)
{
	Mutex();
	time_ = tm; 
	return time_;
}

Maker* DataManager::SetMaker(Maker* maker)
{
	Mutex();
	maker_ = maker;  
	return maker_;
}

WavData* DataManager::SetWav(WavData* wav_data)
{
	Mutex();
	wav_data_ = wav_data;
	return wav_data_;
}

MusicData* DataManager::SetMusicData(MusicData* music_data)
{
	Mutex();
	music_data_ = music_data;
	return music_data_;
}

bool DataManager::SetFinRead(bool t)
{
	Mutex();
	is_fin_read_ = t;
	return is_fin_read_;
}

bool DataManager::SetFinWrite(bool t)
{
	Mutex();
	is_fin_write_ = t;
	return is_fin_write_;
}

bool DataManager::SetEnd(bool t)
{
	Mutex();
	is_end_ = t;
	return is_end_;
}

std::string DataManager::SetTitle(std::string str)
{
	Mutex();
	title_.clear();
	title_.append(str);
	return title_;
}
