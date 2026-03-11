//-----------------------------
// @name   alpha_node.h
// @brief  アルファノード クラスの宣言部
// @auther A.namami
// @date   2026/3/11  新規作成
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "alpha_node.h"
#include "defining.h"

void AlphaNode::Draw(int screen_handle,Camera* camera)
{
	//ブレンドモードを変えて描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_ * window_setting::max_dxlib_param);
}
