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
	play_music_.title = title;
	FileRoader::GetInstance()->RoadMusic(&play_music_);
}

//再生関係
void MusicManager::PlayMusic()
{
	PlaySoundMem(play_music_.handle, DX_PLAYTYPE_BACK);
}

void MusicManager::StopMusic()
{
	//再生中か
	if (CheckSoundMem(play_music_.handle)) {
		StopSoundMem(play_music_.handle);
	}
}

void MusicManager::DeleteMusic()
{
	DeleteSoundMem(play_music_.handle);
}

void MusicManager::PlayBgm()
{
	PlaySoundMem(bgm_handle_, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
}

void MusicManager::StopBgm()
{
	//再生中か
	if (CheckSoundMem(play_music_.handle)) {
		StopSoundMem(bgm_handle_);
	}
}

void MusicManager::EndBgm()
{
	DeleteSoundMem(bgm_handle_);
}
