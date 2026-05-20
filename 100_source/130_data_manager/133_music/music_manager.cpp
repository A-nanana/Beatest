//-----------------------------
// @name   music_manager.cpp
// @brief  楽曲管理 クラス
// @auther A.namami
// @date   2026/3/6  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "DxLib.h"
#include "../../140_roading_from_other/file_roader.h"
#include "../../110_drawing_tools/defining.h"
#include "../../110_drawing_tools/tool.h"
#include "music_manager.h"

MusicManager* MusicManager::music_manager_ = nullptr;

MusicManager::MusicManager()
{
}

MusicManager::~MusicManager()
{
	//初期化
	InitSoundMem();
}

MusicManager* MusicManager::GetInstance() {
	//既にインスタンスがあるか
	if (music_manager_ == nullptr) {
		music_manager_ = new MusicManager();
	}
	return music_manager_;
}

void MusicManager::SetPlayMusic(const LineUp& line_up)
{
	play_music_.title_ = line_up.title;
	play_music_.music_key_ = line_up.music_key;
	play_music_.high_score_ = line_up.high_score[play_music_.defficult].value_or(window_setting::null_param);
	FileRoader::GetInstance()->RoadMusic(&play_music_);
}

void MusicManager::SetLineUp()
{
	//既にあるなら読み込まない
	if (!title_line_up_.empty()) {
		return;
	}
	FileRoader::GetInstance()->RoadLineup(&title_line_up_);
	//何かあるか
	if (title_line_up_.size() > NULL) {
		return;
	}
	//入ってないことを教える
	title_line_up_.push_back({ string_set::unknown ,NULL});
}

void MusicManager::SetSe()
{
	for (int i = 0; i < k_se_max; i++) {
		se_handle_[i] = FileRoader::GetInstance()->RoadSe(i);
	}
}

void MusicManager::SetBgm()
{
	bgm_handle_ = FileRoader::GetInstance()->RoadBgmDef();
}

void MusicManager::SetHighScore(int score)
{
	play_music_.high_score_ = score;
	//ラインナップも書き換え
	for (int i = 0;i < title_line_up_.size();i++) {
		//キーの一致を確認する
		if (title_line_up_[i].music_key == play_music_.music_key_) {
			title_line_up_[i].high_score[play_music_.defficult] = score;
		}
	}
}

void MusicManager::SetDefficult(int nanido)
{
	play_music_.defficult = nanido;

}

//再生関係
void MusicManager::PlayMusic()
{
	//ハンドルの有無
	if (play_music_.handle_ == -1) {
		return;
	}
	//再生中か
	if (CheckSoundMem(play_music_.handle_)) {
		return;
	}
	PlaySoundMem(play_music_.handle_, DX_PLAYTYPE_BACK);
}

void MusicManager::RePlayMusic()
{
	//ハンドルの有無
	if (play_music_.handle_ == -1) {
		return;
	}
	//再生中か
	if (CheckSoundMem(play_music_.handle_)) {
		return;
	}
	PlaySoundMem(play_music_.handle_, DX_PLAYTYPE_BACK,FALSE);
}

void MusicManager::StopMusic()
{
	//ハンドルの有無
	if (play_music_.handle_ == -1) {
		return;
	}
	//再生中か
	if (CheckSoundMem(play_music_.handle_)) {
		StopSoundMem(play_music_.handle_);
	}
}

void MusicManager::DeleteMusic()
{
	//ハンドルの有無
	if (play_music_.handle_ == -1) {
		return;
	}
	DeleteSoundMem(play_music_.handle_);
}

void MusicManager::PlayBgm()
{
	//ハンドルの有無
	if (bgm_handle_ == -1) {
		return;
	}
	//再生中か
	if (CheckSoundMem(bgm_handle_)) {
		return;
	}
	PlaySoundMem(bgm_handle_, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
}

void MusicManager::StopBgm()
{
	//ハンドルの有無
	if (bgm_handle_ == -1) {
		return;
	}
	//再生中か
	if (CheckSoundMem(bgm_handle_)) {
		StopSoundMem(bgm_handle_);
	}
}

void MusicManager::EndBgm()
{
	if (bgm_handle_ == -1) {
		return;
	}
	DeleteSoundMem(bgm_handle_);
}

void MusicManager::PlaySe(int se_type)
{
	//ハンドルの有無
	if (se_handle_[se_type] == -1) {
		return;
	}
	PlaySoundMem(se_handle_[se_type], DX_PLAYTYPE_BACK);
}

void MusicManager::StopSe(int se_type)
{
	//ハンドルの有無
	if (se_handle_[se_type] == -1) {
		return;
	}
	//再生中か
	if (CheckSoundMem(se_handle_[se_type])) {
		StopSoundMem(se_handle_[se_type]);
	}
}

void MusicManager::EndSe(int se_type)
{
	//ハンドルの有無
	if (se_handle_[se_type] == -1) {
		return;
	}
	DeleteSoundMem(se_handle_[se_type]);
}
