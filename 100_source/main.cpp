//-----------------------------
// @name   main.cpp
// @brief  実装場所
// @auther A.namami
// @date   2026/3/2 新規作成
// @memo   TFはDXライブラリ準拠です
// 
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "110_drawing_tools\defining.h"
#include "110_drawing_tools\inputer.h"
#include "110_drawing_tools\scene_manager.h"
#include "110_drawing_tools\time.h"
#include "140_roading_from_other\file_roader.h"
#include "120_game_scene\top_scene.h"
#include "130_data_manager\133_music\music_manager.h"
#include "130_data_manager\134_other\configs_manager.h"
#include "130_data_manager\134_other/window_manager.h"
#include "../200_resource/250_other/resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	
	WindowManager::GetInstance()->WindowSettings();
	SetMainWindowText(string_set::title);
	SetWindowIconID(IDI_ICON1);
	if (DxLib_Init() == -1) {
		return -1;
	}
	
	SetAlwaysRunFlag(TRUE);
	//Se読み込み
	MusicManager::GetInstance()->SetSe();
	//bgm読み込み
	MusicManager::GetInstance()->SetBgm();

	//シーン設定
	SceneManager* scene_manage = new SceneManager();
	scene_manage->SetNextScene(new TopScene());
	//時間計測用変数
	Time time;
	//裏画面化
	SetDrawScreen(DX_SCREEN_BACK);

	//画面制御用時間確認
	float next_to_time = time.GetDelta();
	float set_last = GetNowCount();

	//メインループ
	while ((ProcessMessage() != -1) && ConfigsManager::GetInstance()->GetDone()) {
		//画面クリア
		ClearDrawScreen();
		//設定系更新
		time.Update();
		Inputer::GetInstance()->Update();

		//描画系更新
		scene_manage->Update(time.GetDelta());
		scene_manage->Draw(DX_SCREEN_BACK);
		ScreenFlip();
		
		
		//fpsの確認
		while (next_to_time < window_setting::sec_per_frame)
		{
			float now = GetNowCount();
			next_to_time += now - set_last;
			set_last = now;
		}
	}
	//終了設定
	DxLib_End();
	return 0;
}