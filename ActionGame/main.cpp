//-----------------------------
// @name   main.cpp
// @brief  ŽÀ‘•êŠ
// @auther A.namami
// @date   2026/3/2 V‹Kì¬
// @memo   TF‚ÍDXƒ‰ƒCƒuƒ‰ƒŠ€‹’‚Å‚·
// 
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "..\100_source\110_drawing_tools\defining.h"
#include "..\100_source\110_drawing_tools\inputer.h"
#include "..\100_source\110_drawing_tools\scene_manager.h"
#include "..\100_source\110_drawing_tools\time.h"
#include "..\100_source\140_roading_from_other\file_roader.h"
#include "..\100_source\110_drawing_tools\game_scene.h"
#include "..\100_source\120_game_scene\top_scene.h"
#include "..\100_source\130_data_manager\133_music\music_manager.h"

int main(void) {
	
	
	window_setting::WindowSettings();

	if (DxLib_Init() == -1) {
		return -1;
	}
	
	SetAlwaysRunFlag(TRUE);
	

	SceneManager* scene_manage = new SceneManager();
	scene_manage->SetNextScene(new TopScene());
	Time time;

	SetDrawScreen(DX_SCREEN_BACK);

	float next_to_time = time.GetDelta();
	float set_last = GetNowCount();

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		time.Update();
		Inputer::GetInstance()->Update();

		scene_manage->Update(time.GetDelta());
		scene_manage->Draw(DX_SCREEN_BACK);
		ScreenFlip();
		
		
		
		while (next_to_time < window_setting::sec_per_frame)
		{
			float now = GetNowCount();
			next_to_time += now - set_last;
			set_last = now;
		}
	}
	
	DxLib_End();
	return 0;
}