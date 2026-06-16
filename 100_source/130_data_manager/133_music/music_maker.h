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
#pragma once


#include <iostream>
#include <mutex>

#include "chanks.h"

#include "../../160_tenplated/manager_tenplate.h"

//ファイル管理
class MusicMakerWant;
class MusicMaker:public Singleton<MusicMaker>
{
public:
	 bool GetFile(std::string* name, WavData* &get_data, int* tag_rate, int* second_length);//ファイル入手
	 bool WriteFile(std::string* name, std::string* param);//ファイル出力
	 bool WritePropaty(std::string* name,MusicMakerWant* param,int second_length);//プロパティ追加
};

