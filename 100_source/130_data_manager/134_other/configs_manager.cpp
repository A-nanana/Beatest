//-----------------------------
// @name   configs_manager.cpp
// @brief  設定管理 クラス
// @auther A.namami
// @date   2026/3/16  新規作成
// @memo   
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "DxLib.h"
#include "configs_manager.h"
#include "..\133_music\music_manager.h"
#include "..\..\110_drawing_tools\defining.h"

ConfigsManager* ConfigsManager::instance_ = nullptr;

//コンストラクタ
ConfigsManager::ConfigsManager() {

	//音量の初期化
	for (int i = 0; i < k_scene_max; i++) {
		vol_music_[i] = window_setting::first_music_vol_percent;
		vol_se_[i] = window_setting::first_se_vol_percent;
	}
}

//  アクセス
ConfigsManager* ConfigsManager::GetInstance() {
	if (instance_ == nullptr) {
		instance_ = new ConfigsManager();
	}
	return instance_;
}

//  ゲッター
int ConfigsManager::GetVolMusic(SceneIf scene) {
	return vol_music_[scene];
}
int ConfigsManager::GetVolSe(SceneIf scene) {
	return vol_se_[scene];
}

int ConfigsManager::GetIt(Configs param)
{
	//項目で処理分岐
	switch (param)
	{
	case k_scene_game_music:
		return GetVolMusic(k_scene_game);
		break;
	case k_scene_game_se:
		return GetVolSe(k_scene_game);
		break;
	case k_scene_main_music:
		return GetVolMusic(k_scene_main);
		break;
	case k_scene_main_se:
		return GetVolSe(k_scene_main);
		break;
	default:
		break;
	}
	return 0;
}

//  増減
int ConfigsManager::AddVolMusic(SceneIf scene) {
	//最大でなければ増加
	if (vol_music_[scene] < window_setting::percent_max) {
		vol_music_[scene]++;
	}
	return vol_music_[scene];
}
int ConfigsManager::SubVolMusic(SceneIf scene) {
	//最小でなければ減少
	if (vol_music_[scene] > window_setting::null_param) {
		vol_music_[scene]--;
	}
	return vol_music_[scene];
}
int ConfigsManager::AddVolSe(SceneIf scene) {
	//最大でなければ増加
	if (vol_se_[scene] < window_setting::percent_max) {
		vol_se_[scene]++;
	}
	return vol_se_[scene];

}
int ConfigsManager::SubVolSe(SceneIf scene) {
	//最小でなければ減少
	if (vol_se_[scene] > window_setting::null_param) {
		vol_se_[scene]--;
	}
	return vol_se_[scene];

}

int ConfigsManager::AddIt(Configs param)
{
	//項目で処理分岐

	switch (param)
	{
	case k_scene_game_music:
		return AddVolMusic(k_scene_game);
		break;
	case k_scene_game_se:
		return AddVolSe(k_scene_game);
		break;
	case k_scene_main_music:
		return AddVolMusic(k_scene_main);
		break;
	case k_scene_main_se:
		return AddVolSe(k_scene_main);
		break;
	default:
		break;
	}
}

int ConfigsManager::SubIt(Configs param)
{
	//項目で処理分岐

	switch (param)
	{
	case k_scene_game_music:
		return SubVolMusic(k_scene_game);
		break;
	case k_scene_game_se:
		return SubVolSe(k_scene_game);
		break;
	case k_scene_main_music:
		return SubVolMusic(k_scene_main);
		break;
	case k_scene_main_se:
		return SubVolSe(k_scene_main);
		break;
	default:
		break;
	}
}

//適用
void ConfigsManager::SetIt()
{

	ChangeVolumeSoundMem(vol_music_[k_scene_main] * window_setting::max_dxlib_param, MusicManager::GetInstance()->GetBgmHandle());

	//楽曲再生時用以外のseのみ取り出して設定
	ChangeVolumeSoundMem(vol_se_[k_scene_main] * window_setting::max_dxlib_param, MusicManager::GetInstance()->GetSeHandle(k_select));
}

void ConfigsManager::SetMusic()
{
	ChangeVolumeSoundMem(vol_music_[k_scene_game] * window_setting::max_dxlib_param, MusicManager::GetInstance()->GetMusicData().handle_);
	
	//楽曲再生時用のseのみ取り出して設定
	ChangeVolumeSoundMem(vol_se_[k_scene_game] * window_setting::max_dxlib_param, MusicManager::GetInstance()->GetSeHandle(k_play_critical));


}
