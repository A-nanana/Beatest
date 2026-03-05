//-----------------------------
// @name   camera.h
// @brief  カメラ クラス
// @auther A.namami
// @date   2026/3/3  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Vector2.h"
class Camera
{
public:
	Vector2D position_;//位置(カメラの左端位置)
	Vector2D size_;//描画サイズ
	Vector2D player_pos_;//プレイヤーとの相対位置
//  コンストラクタ
	Camera(float x, float y);
	void Init();//初期化
	void Update();//更新
	bool IsDraw(Vector2D world_pos);//描画すべきか
};

#endif // !__CAMERA_H__

