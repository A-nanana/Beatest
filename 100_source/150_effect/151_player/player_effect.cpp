//-----------------------------
// @name   player_effect.cpp
// @brief  プレイヤーエフェクト クラス
// @auther A.namami
// @date   2026/3/11  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "player_effect.h"
#include "..\..\110_drawing_tools\defining.h"

void PlayerEffect::SetUp() {
	SetPosition(NULL, NULL);
}

void PlayerEffect::Update(float delta_time) {

}

PlayerEffect::PlayerEffect()
{

}

void PlayerEffect::Create(int flg)
{
	//フラグで切り替え
	if (flg & effect_set::effect_critical) {
		
	}
}
