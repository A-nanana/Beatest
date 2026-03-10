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

#include <vector>
#include <string>
//------------------------------
// @name   MusicData
// @brief  楽曲データ 構造体
// @memo   
//------------------------------
struct MusicData {
	std::string title_;//タイトル
	int bpm_;//bpm
	float time_;//時間
	int hyousi_;//拍子
	float ms_per_hyousi_;//1拍当たりの秒数
	int handle_; //楽曲ハンドル
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
	std::vector<std::string> title_line_up_;//タイトルのラインナップ
	int bgm_handle_;//bgmのハンドル
//  コンストラクタ
	MusicManager();
//  デストラクタ
	~MusicManager();
public:
//  インスタンスアクセス
	static MusicManager* GetInstance();
//  複製防止
	MusicManager operator= (const MusicManager&) = delete;
	MusicManager& operator= (MusicManager&) = delete;

//  セッター
	void SetPlayMusic(const char* title);//タイトルで設定
	void SetLineUp();//ラインナップ設定

//  ゲッター
	int GetBpm() { return play_music_.bpm_; };//bpm取得
	std::string GetTitle() { return play_music_.title_; };//タイトル取得
	int GetMusicTime() { return play_music_.time_; };//時間(s)
	MusicData GetMusicData() { return play_music_; };//データ取得
	float GetMsPerHyousi() { return play_music_.ms_per_hyousi_; }; //1拍当たりの秒数(ms)
	std::string operator[](int i) { return title_line_up_[i]; }; //ラインナップからタイトル取得
	int GetLineupSize() { return title_line_up_.size(); };//リストサイズ


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
