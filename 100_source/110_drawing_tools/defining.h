//-----------------------------
// @name   defining_drawing.h
// @brief  描画で使う数を定義する場所
// @auther A.namami
// @date   2026/2/26 新規作成
// @memo   TFはDXライブラリ準拠です
//         項目ごとに名前空間で分けてます
// 
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#ifndef __DEFINING_DRAWING_H__
#define __DEFINING_DRAWING_H__

#define _USE_MATH_DEFINES

#include <math.h> //数学ライブラリ
//-----------------------------
// @name   window_setting
// @brief  ウィンドウ関係
// @memo   
//------------------------------
namespace window_setting {
//  ウィンドウサイズ
	static int size_x = 800; // x
	static int size_y = 600; // y
//  カラービット
	static int color_bit = 32;
//  ウィンドウの中央位置
	static int center_x = 400; // x
	static int center_y = 200; // y
//  ウィンドウの表示猶予
	static int offset_shown = 100;
//  画像拡大率
	static float graph_extender_ = 0.5f;
//  fps
	static const int fps = 60;
//  fpsから1コマあたりの時間を出す
	static const float sec_per_frame = 1000.0f / fps;
//  ウィンドウの初期設定を一括でする関数
	void WindowSettings();
}

//-----------------------------
// @name   ege_set
// @brief  ウィンドウ端関数
// @memo   
//------------------------------
namespace ege_set {
//  端の空白(文字開始位置)
	static const int brank_x = 64; // x
	static const int brank_y = 64; // y
//  端の空白(バー開始位置)
	static const int bar_brank_x = 4; // x
	static const int bar_brank_y = 4; // y
}

//-----------------------------
// @name   line_set
// @brief  行や列関係
// @memo   
//------------------------------
namespace line_set {
//  間の空白
	static const int brank_x = 32; // x
	static const int brank_y = 32; // y
//  最大で並べられる数
	static const int amount_x_max = 4; // x
	static const int amount_y_max = 5; // y

}

//-----------------------------
// @name   buttom_set
// @brief  ボタン関係
// @memo   
//------------------------------
namespace buttom_set {
//  サイズ
	static const int size_x = 64; // x
	static const int size_y = 32; // y
}

//-----------------------------
// @name   hit_set
// @brief  当たり判定関係
// @memo   
//------------------------------
namespace hit_set {
//  頂点の数
	static const int squair_point = 4;
//  

}

//-----------------------------
// @name   string_set
// @brief  表示する文字関係
// @memo   
//------------------------------
namespace string_set {
//  不定値(値がわからないとき)
	static const char* unknown = " ? ";
//  トップの文字
	static const char* title = " Beatest ";
//  動作系
	static const char* push_to_start = "push Enter to start"; //開始

}


//-----------------------------
// @name   system_set
// @brief  ゲームシステム関係
// @memo   
//------------------------------
namespace system_set {
//  プレイヤーの速さ
	static const float player_walk_speed = 5.0f;
//  弾のデフォルトの速さ
	static const float shot_speed_def = 10;
//  角度が大きくなったときの修正角度
	static const float repair_rad = M_PI * 270.0f / 180.0f;
//  猶予時間
	static const float border_time = 34.0f;
//  1sをmsに直す
	static const int ms_per_s = 1000;
//  弾の角度修正単位
	static const float angle_per_time = 15.0f * M_PI / 180.0f;
//  画面上の弾数
	static const int shot_max = 100;
//  弾の種類
	static const enum ShotType {
		ENEMY_NOMAL,

	};


}

#endif // !__DEFINING_DRAWING_H__



