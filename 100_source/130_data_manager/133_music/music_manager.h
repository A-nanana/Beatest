//-----------------------------
// @name   music_manager.h
// @brief  楽曲管理 クラス
// @auther A.namami
// @date   2026/3/6  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __MUSIC_MANAGER_H__
#define __MUSIC_MANAGER_H__

#include <string>
//------------------------------
// @name   MusicData
// @brief  楽曲データ 構造体
// @memo   エラー型が来た場合は-1で返します
//------------------------------
struct MusicData {
	std::string title;//タイトル
	int bpm;//bpm
	float time;//時間
	int handle; //楽曲ハンドル
};

//------------------------------
// @name   MusicManager
// @brief  楽曲管理 クラス
// @memo   エラー型が来た場合は-1で返します
//------------------------------
class MusicManager
{
	static MusicManager* music_manager_; // 楽曲管理インスタンス
	MusicData play_music_; //演奏中楽曲データ
	int bgm_handle_;//bgmのハンドル
//  コンストラクタ
	MusicManager();
//  デストラクタ
	~MusicManager();
public:
//  インスタンスアクセス
	static MusicManager* GetInstance();
//  セッター
	void SetPlayMusic(const char* title);
//  ゲッター
	int GetBpm() { return play_music_.bpm; };
	std::string GetTitle() { return play_music_.title; };
	MusicData GetMusicData() { return play_music_; };
//  通常再生関係
	void PlayMusic();
	void StopMusic();
	void DeleteMusic();
//  BGM再生関係
	void PlayBgm();
	void StopBgm();
	void EndBgm();

};

#endif // !__MUSIC_MANAGER_H__
