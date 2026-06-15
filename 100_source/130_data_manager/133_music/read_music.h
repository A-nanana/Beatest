//-----------------------------
// @name   read_music.h
// @brief  曲分析 クラス
// @auther A.namami
// @date   2026/6/5  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __READ_WAV_H__
#define __READ_WAV_H__


#include <iostream>
#include "../../140_roading_from_other/dr_mp3.h"

#include "chanks.h"
#include "../../160_tenplated/manager_tenplate.h"

class ReadWav :public Singleton<ReadWav>
{
	
public:
	WavData* ReadIt(FILE* file);
};

class ReadMp3 :public Singleton<ReadMp3>
{

public:
	WavData* ReadIt(drmp3* file);
};


#endif // !__READ_WAV_H__
