//-----------------------------
// @name   data_manager.h
// @brief  共有データ管理 クラス
// @auther A.namami
// @date   2026/6/11  新規作成
//         2026/6/15  取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#pragma once

#include <mutex>

#include "../../160_tenplated/manager_tenplate.h"
#include "maker.h"
#include "../133_music/music_maker.h"

//譜面制に必要なプロパティ
struct MusicMakerWant {
	int bpm;//bpm
	int hakusuu;//拍子
};

//データ管理用
class DataManager:public Singleton<DataManager>
{
	std::mutex mtx_;//ロック管理

	std::string title_;//タイトル
	Maker* maker_;//譜面作成機
	WavData* wav_data_;//波長データ
	MusicMakerWant * music_data_;//譜面作成用追加データ
	
	int tag_time_; //記録位置
	int time_;//時間
	
	bool is_fin_read_;//読込の終了
	bool is_fin_write_;//書き込みの終了
	bool is_end_;//終了タイミング

public:

	//取得関係(データ)
	Maker GetMaker();
	WavData GetWav();
	MusicMakerWant  GetMusicMakerWant ();

	int GetTagTimr();
	int GetTime();

	bool GetFinRead();
	bool GetFinWrite();
	bool GetEnd();

	std::string GetTitle();

	//設定関係(設定後の値を返す)
	int SetTagTime(int tag_time);
	int SetTime(int tm);
	
	Maker* SetMaker(Maker* maker);
	WavData* SetWav(WavData* wav_data);
	MusicMakerWant * SetMusicMakerWant (MusicMakerWant * music_data);

	bool SetFinRead(bool t);
	bool SetFinWrite(bool t);
	bool SetEnd(bool t);

	std::string SetTitle(std::string str);
};

