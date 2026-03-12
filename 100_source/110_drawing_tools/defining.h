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

//  ウィンドウの端直線距離
	static int length = 400;

//  画像拡大率
	static float graph_extender_ = 0.25f;

//  fps
	static const int fps = 60;
//  fpsから1コマあたりの時間を出す
	static const float sec_per_frame = 1000.0f / fps;

//  0(iostream入れないとNULLを使えなさそう)
	static const int null_param = 0;

//  255(DxLibの要素指定で最大値になりそう)
	static const int max_dxlib_param = 255;

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
//  セレクター系の初期位置
	static const int selecter_x = window_setting::center_x / 3;//x
	static const int selecter_y = window_setting::size_y / 3;//y
//  見出しの初期配置
	static const int midasi_y = window_setting::center_y / 2;//y
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
	static const int squair_point = 4;//四角
	static const int size_per_point = 2;//点1つあたりの半径(なめらかに見せたい)
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
	static const char* select_song = "Select To Play!";//選択
	static const char* result = "Your Result"; //結果
//  名詞
	static const char* conbo = "C O N B O !"; //結果
	static const char* score = "Score";//スコア
	static const char* max_conbo = "Max Conbo";//最大コンボ
}

//-----------------------------
// @name   score_set
// @brief  スコア関係
// @memo   
//------------------------------
namespace score_set {
//  クリティカル
	static const int per_critical = 1000;
//  ちょっと回避
	static const int per_avoiding = 500;
//  がっつり回避
	static const int per_none = 100;

}

//-----------------------------
// @name   effect_set
// @brief  エフェクト関係
// @memo   ビット演算が前提です
//------------------------------
namespace effect_set {
//  当たり判定のエフェクト
	static const int effect_critical = 1 << 0;//クリティカル
	static const int effect_avoid = 1 << 1;//ちょい避け
	static const int effect_none = 1 << 2; //がっつり避け
}
//-----------------------------
// @name   effect_param
// @brief  エフェクト値
// @memo   ビット演算が前提です
//------------------------------
namespace effect_param {
//  ループ関係
	static const int loop_hit = 1;//ループ回数
	static const float time_per_loop = 500;// 1ループ当たりの時間(ms)

//  広がり関係
	//外への広がり
	static const float pos_out_x = 1.0f;//x
	static const float pos_out_y = 1.0f;//y

//  太さ関係
	static const float eff_thick = 2.0;//太さ(基本これ)
	static const float back_thick = 5.0;//太さ(背景エフェクト)

//  アルファ関係
	static const float back_alpha = 0.4f;//背景エフェクトの透明度

}

//-----------------------------
// @name   system_set
// @brief  ゲームシステム関係
// @memo   
//------------------------------
namespace system_set {
//  プレイヤーの速さ
	static const float player_walk_speed = 10.0f;
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
	static const int shot_max = 1000;
//  弾の種類
	static const enum ShotType {
		ENEMY_NOMAL,

	};
//  必須待機時間
	static const int need_wait_time_ = 0.2 * ms_per_s;

//  判定開始距離
	static const float start_hit_check = 70.0f;
//  クリティカルチェック基準距離
	static const float critical_hit_check = 35.0f;

}

#endif // !__DEFINING_DRAWING_H__



