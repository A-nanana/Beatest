//-----------------------------
// @name   maker.h
// @brief  譜面作成 クラス
// @auther A.namami
// @date   2026/6/8  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __HUMEN_MAKER_H__
#define  __HUMEN_MAKER_H__
#include <iostream>
#include <string>
#include "chanks.h"

class Maker
{
	static int last_none_time; //最後に何もない時間(s)
	uint32_t buffer_;//余り
	int buffer_count_;//読み込み量カウント
	int count_time_;//拍子間カウント
	int bunkatu_;//チャンネルカウント
	int sec_count_;//セクションカウント
	int* serch_time_;//乱数入れ
	int hakusuu_;//曲の拍数
	std::vector<int> sec_top_;//取り出しデータ


	bool Init();// データ初期化
	bool SetData(int diff);
public:	
	bool GetTopData(WavData* datas, int tag_time, int bpm, int length);
	std::string* MakeHumen(WavData* datas,int bpm,int diff, int hakusuu,int tag_time, int length);
};


#endif // !__HUMEN_MAKER_H__
