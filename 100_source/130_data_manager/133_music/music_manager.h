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
	int high_score_;//最高スコア
	unsigned int defficult;//難易度

	float ms_per_hyousi_;//1拍当たりの秒数
	int handle_; //楽曲ハンドル
};

//------------------------------
// @name   LineUp
// @brief  ラインナップデータ 構造体
// @memo   
//------------------------------
struct LineUp
{
	std::string title; //タイトル
	int high_score;//最高スコア
	std::uint8_t defficalt_flg_;//難易度フラグ
};

//Se指定用
enum SeType {
	k_select,//選択時のse
	k_play_critical,//クリティカル判定のse
	k_se_max
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
	std::vector<LineUp> title_line_up_;//タイトルのラインナップ
	int bgm_handle_;//bgmのハンドル
	int se_handle_[k_se_max];//seのハンドル
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
	void SetSe();//Se設定
	void SetBgm();//bgm設定
	void SetHighScore(int score);//スコア設定
	void SetDefficult(int nanido);//難易度設定

//  ゲッター
	int GetBpm() { return play_music_.bpm_; };//bpm取得
	std::string GetTitle() { return play_music_.title_; };//タイトル取得
	int GetMusicTime() { return play_music_.time_; };//時間(s)
	int GetMusicHighScore() { return play_music_.high_score_; };//最高スコア

	MusicData GetMusicData() { return play_music_; };//データ取得

	float GetMsPerHyousi() { return play_music_.ms_per_hyousi_; }; //1拍当たりの秒数(ms)

	LineUp operator[](int i) { return title_line_up_[i]; }; //ラインナップから1作品取得
	int GetLineupSize() { return title_line_up_.size(); };//リストサイズ

	int GetSeHandle(int se_type) { return se_handle_[se_type]; };//seのハンドル

	int GetBgmHandle() { return bgm_handle_; };//bgmのハンドル

//  通常再生関係
	void PlayMusic();//再生
	void RePlayMusic();//途中再生

	void StopMusic();//止め
	void DeleteMusic();//ハンドル消去
//  BGM再生関係
	void PlayBgm();//再生
	void StopBgm();//止め
	void EndBgm();//ハンドル消去
//  Se再生関係
	void PlaySe(int se_type);//再生
	void StopSe(int se_type);//止め
	void EndSe(int se_type);//ハンドル消去

};

#endif // !__MUSIC_MANAGER_H__
