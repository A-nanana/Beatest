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

Maker DataManager::GetMaker()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return *maker_;
}

WavData DataManager::GetWav()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return *wav_data_;
}

MusicMakerWant DataManager::GetMusicMakerWant()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return *music_data_;
}

int DataManager::GetTagTimr()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return tag_time_;
}

int DataManager::GetTime()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return time_;
}

bool DataManager::GetFinRead()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return is_fin_read_;
}

bool DataManager::GetFinWrite()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return is_fin_write_;
}

bool DataManager::GetEnd()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return is_end_;
}

std::string DataManager::GetTitle()
{
	std::lock_guard<std::mutex> lock_(mtx_);
	return title_;
}

int DataManager::SetTagTime(int tag_time) {
	std::lock_guard<std::mutex> lock_(mtx_);
	tag_time_ = tag_time;
	return tag_time_; 
}

int DataManager::SetTime(int tm)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	time_ = tm; 
	return time_;
}

Maker* DataManager::SetMaker(Maker* maker)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	maker_ = maker;  
	return maker_;
}

WavData* DataManager::SetWav(WavData* wav_data)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	wav_data_ = wav_data;
	return wav_data_;
}

MusicMakerWant* DataManager::SetMusicMakerWant(MusicMakerWant* music_data)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	music_data_ = music_data;
	return music_data_;
}

bool DataManager::SetFinRead(bool t)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	is_fin_read_ = t;
	return is_fin_read_;
}

bool DataManager::SetFinWrite(bool t)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	is_fin_write_ = t;
	return is_fin_write_;
}

bool DataManager::SetEnd(bool t)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	is_end_ = t;
	return is_end_;
}

std::string DataManager::SetTitle(std::string str)
{
	std::lock_guard<std::mutex> lock_(mtx_);
	title_.clear();
	title_.append(str);
	return title_;
}
