//-----------------------------
// @name   scene.h
// @brief  シーン クラスの宣言部
// @auther A.namami
// @date   2026/2/18  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once
#include "defining.h"
#include "camera.h"
class Scene
{
protected:
	Camera* camera_;//描画の中心を保存する
public:
//  コンストラクタ
	Scene() {};
//  デストラクタ
	virtual ~Scene() {};

//  初期化
	virtual void Init() = 0;
//  準備
	virtual void SetUp() = 0;
//  終了
	virtual void Finalize() = 0;
//  更新
	virtual Scene* Update(float delta_time) = 0;
//  描画
	virtual void Draw(int screen_handle) = 0;

};

