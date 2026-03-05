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
#include "..\100_source\110_drawing_tools\game_scene.h"

int main(void) {

	if (DxLib_Init() == -1) {
		return -1;
	}
	
	window_setting::WindowSettings();
	SceneManager* scene_manage = new SceneManager();
	scene_manage->SetNextScene(new GameScene());
	Time time;

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		time.Update();
		Inputer::GetInstance()->Update();

		scene_manage->Update(time.GetDelta());
		scene_manage->Draw(DX_SCREEN_BACK);
		ScreenFlip();

	}
	
	DxLib_End();
	return 0;
}