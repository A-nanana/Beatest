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
#include "..\..\140_roading_from_other\file_roader.h"
#include "..\..\110_drawing_tools\defining.h"
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

void MusicManager::SetPlayMusic(const char* title)
{
	play_music_.title_ = title;
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
}

//再生関係
void MusicManager::PlayMusic()
{
	if (play_music_.handle_ == -1) {
		return;
	}
	PlaySoundMem(play_music_.handle_, DX_PLAYTYPE_BACK);
}

void MusicManager::StopMusic()
{
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
	if (play_music_.handle_ == -1) {
		return;
	}
	DeleteSoundMem(play_music_.handle_);
}

void MusicManager::PlayBgm()
{
	if (bgm_handle_ == -1) {
		return;
	}
	PlaySoundMem(bgm_handle_, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
}

void MusicManager::StopBgm()
{
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
	if (se_handle_[se_type] == -1) {
		return;
	}
	PlaySoundMem(se_handle_[se_type], DX_PLAYTYPE_BACK);
}

void MusicManager::StopSe(int se_type)
{
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
	if (se_handle_[se_type] == -1) {
		return;
	}
	DeleteSoundMem(se_handle_[se_type]);
}
