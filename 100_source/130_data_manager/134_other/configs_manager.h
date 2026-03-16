//-----------------------------
// @name   configs_manager.h
// @brief  設定管理 クラス
// @auther A.namami
// @date   2026/3/16  新規作成
// @memo   
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#ifndef __CONFIG_MANAGHER_H__
#define __CONFIG_MANAGHER_H__

//------------------------------
// @name   SceneIf
// @brief  適応シーンタグ
// @memo   
//------------------------------
enum SceneIf{
	scene_main = 0, //選択シーン
	scene_game ,//ゲームシーン
	scene_max  //最大値
	
};

//項目識別用
enum Configs {
	scene_game_music,//ゲームシーン曲
	scene_game_se,//ゲームシーンSe
	scene_main_music, //選択シーン曲
	scene_main_se, //選択シーンSe
	config_amount //最大値
};

//------------------------------
// @name   ConfigsManager
// @brief  設定管理 クラス
// @memo   
//------------------------------
class ConfigsManager
{
	static ConfigsManager* instance_;// 実体
	
	int vol_music_[scene_max];//曲音量
	int vol_se_[scene_max];//SE音量


//  コンストラクタ
	ConfigsManager();
//  デストラクタ
	~ConfigsManager() {};

public:
//  複製防止
	ConfigsManager operator= (const ConfigsManager&) = delete;
	ConfigsManager& operator= (ConfigsManager&) = delete;
//  アクセス
	static ConfigsManager* GetInstance();

//  ゲッター
	int GetVolMusic(SceneIf scene);//曲音量
	int GetVolSe(SceneIf scene);//SE音量
	int GetIt(Configs param);//項目に沿って取得

//  増減
	int AddVolMusic(SceneIf scene);//曲音量増加
	int SubVolMusic(SceneIf scene);//曲音量減少
	int AddVolSe(SceneIf scene);//Se音量増加
	int SubVolSe(SceneIf scene);//Se音量減少

	int AddIt(Configs param);//項目に沿って増加
	int SubIt(Configs param);//項目に沿って減少

//  セット
	void SetIt();//適用
	void SetMusic();//ゲーム前に呼び出す方

};


#endif // !__CONFIG_MANAGHER_H__
