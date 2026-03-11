//-----------------------------
// @name   player_effect.h
// @brief  プレイヤーエフェクト クラス
// @auther A.namami
// @date   2026/3/11  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __PLAYER_EFFECT_H__
#define __PLAYER_EFFECT_H__

#include "..\..\110_drawing_tools\node.h"

class PlayerEffect:public Node
{
	
	
	//ロード
	void Load() {};
	//リソース解放
	void Release() {};
	//セット
	void SetUp();
	//更新(更新するときの時間)
	void Update(float delta_time);
	//描画(描画先)
	void Draw(int screen_handle, Camera* camera) {};
public:
//  コンストラクタ
	PlayerEffect();
	
//  エフェクト作成(対応フラグ)
	void Create(int flg);
};


#endif // !__PLAYER_EFFECT_H__
