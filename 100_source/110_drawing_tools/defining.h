//-----------------------------
// @name   defining.h
// @brief  数を定義する場所
// @auther A.namami
// @date   2026/2/26 新規作成
// @memo   
//         随時更新、
//         項目ごとに名前空間で分けてます
//         時間単位はms
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
// @memo   初期値管理用
//------------------------------
namespace window_setting {
//  ウィンドウサイズ
	static int size_x = 800; // x
	static int size_y = 600; // y
//  カラービット
	static int color_bit = 32;
//  ポップアップの大きさ(ウィンドウとの相対倍率)
	static const float pop_up_extend_x = 0.5f; //x
	static const float pop_up_extend_y = 0.5f; //y

//  ウィンドウの表示猶予
	static int offset_shown = 100;

//  画像拡大率
	static float graph_extender_ = 0.4f;
	static float selecter_extender_ = 0.15f;
	static float player_extender_ = 0.18f;

//  fps
	static const int fps = 60;
//  fpsから1コマあたりの時間を出す
	static const float sec_per_frame = 1000.0f / fps;

//  0(iostream入れないとNULLを使えなさそう)
	static const int null_param = 0;

//  255(DxLibの要素指定で最大値になりそう)
	static const int max_dxlib_param = 255;

//  パーセントの最大
	static const int percent_max = 100;

//  初期の音量の大きさ(%)
	static const int first_music_vol_percent = 50;
	static const int first_se_vol_percent = 25;


}

//-----------------------------
// @name   file_set
// @brief  ファイル名前関係
// @memo   
//------------------------------
namespace file_set {
//  楽曲データベースファイル
	static const char* music_data_file_pass = "200_resource/220_music/";//ファイルパス
	static const char* music_data_base_pass = "200_resource/220_music/music.db";//相対パス
	static const char* music_data_base_table = "GameMusicData";//曲内容テーブル名
	static const char* defficult_data_base_table = "Defficult"; //難易度探索用テーブル
	static const char* score_data_base_table = "Score"; //スコア探索用テーブル
//  チュートリアル文章パス
	static const char* tutorial_memo = "200_resource/tutorial_memo.txt";
//  bgmファイルパス
	static const char* bgm_data_pass = "200_resource/bgm.mp3";//相対パス
//  Seファイルパス
	static const char* cursol_se = "200_resource/240_se/cursol_se.mp3";//カーソル音
	static const char* critical_se = "200_resource/240_se/critical_se.mp3";//ギリギリのとき
//  出典について
	static const char* syutten_memo = "200_resource/syutten.txt";
//  画像ファイルパス
	static const char* player = "200_resource/230_object/player.png"; //プレイヤー
	static const char* enemy = "200_resource/230_object/enemy.png"; //敵
	static const char* shot = "200_resource/230_object/bullet.png"; //弾
	static const char* lazer = "200_resource/230_object/lazer.png"; //レーザー
	static const char* selecter = "200_resource/230_object/selecter.png"; //選択のカーソル

	static const char* play_back_defalt = "200_resource/210_back_grounds/back_def.png";//ゲーム中のデフォルト背景
	static const char* menu_back_defalt = "200_resource/210_back_grounds/main_back_def.png";//メニューのデフォルト背景
	
	static const char* title_top = "200_resource/250_other/title_top.png"; //タイトル

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
	static const int brank_y = 48; // y
//  最大で並べられる数
	static const int amount_x_max = 4; // x
	static const int amount_y_max = 5; // y
//  セレクター系の位置補正値
	static const int selecter_pos_x = 0;//x
	static const int selecter_pos_y = 65;//y
//  見出しの初期配置
	static const int midasi_y = 60;//y
//  結果の位置
	static const int reslt_y = 50; //y
//  トップ画面の初期位置
	static const int title_y = 250; //y
	static const int push_txt_y = 350; //y

}

//-----------------------------
// @name   font_set
// @brief  フォント関係
// @memo   
//------------------------------
namespace font_set {
//  見出しのフォントサイズ
	static const int midasi_size_1 = 32;
	static const int midasi_size_2 = 20;
//  フォントの名前
	static const char* midasi_font_name_1 = "UDゴシック";
//  フォントの太さ
	static const int midasi_thick_1 = 2;

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
	static const char* push_to_return = "push Enter to return"; //戻る(エンターで)
	static const char* push_to_end = "push Escape to end"; //終了する(Escで)
	static const char* select_menu = "Menu";//選択
	static const char* select_song = "Select To Play!";//選択
	static const char* config_set = "Set Config";//設定
	static const char* result = "Your Result"; //結果
	static const char* game_finish = "Game Set !";//終了
//  名詞
	static const char* conbo = "C O N B O !"; //結果
	static const char* score = "Score";//スコア
	static const char* high_score = "HighScore";//最高スコア
	static const char* max_conbo = "Max Conbo";//最大コンボ
	static const char* cursol = "->"; //カーソル
//  フォント設定用
	static const char* font_midasi1 = "Midasi1";
	static const char* font_midasi2 = "Midasi2";

	static const char* result_uchiwake[4] =
	{ "Critical",
	"Great",
	"Miss",
	"Good" };//コンボ内訳項目

	static const char* configs[4] =
	{"Game Music",
	"Game SE",
	"Home Music",
	"Home SE"};//調整項目

	static const char* menu[4] =
	{
		"Play (ゲームプレイ！)",
		"Config or End Game(設定)",
		"Credit (素材の出典情報)",
		"About (説明はココ！)"
	};//メニュー項目

	static const char* defficult[4] =
	{
		"Easy",
		"Nomal",
		"Hard",
		"Beyond"
	};//難易度

	static const char* continue_check[2] =
	{
		"P:このまま続ける",
		"Q:選択画面に戻る",
	};//確認用
	
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
//  レーザー回避
	static const int per_lazer = 600;
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
//  判定成功　//

//  ループ関係
	static const int loop_hit = 1;//ループ回数
	static const float time_per_loop = 250;// 1ループ当たりの時間(ms)

//  広がり関係
	//外への広がり
	static const float pos_out_x = 1.0f;//x
	static const float pos_out_y = 1.0f;//y

//  太さ関係
	static const float eff_thick = 2.0;//太さ(基本これ)
	static const float back_thick = 5.0;//太さ(背景エフェクト)

//  アルファ関係
	static const float back_alpha = 0.4f;//背景エフェクトの透明度

//  スコア表示エフェクト
	static const int wait_score = 50;//スコア表示の間の待機時間
}

//-----------------------------
// @name   system_set
// @brief  ゲームシステム関係
// @memo   
//------------------------------
namespace system_set {
//  プレイヤーの速さ
	static const float player_walk_speed = 12.0f;
//  プレイヤーの当たり判定サイズ
	static const float player_hit_size_x = 40.0f;//x
	static const float player_hit_size_y = 40.0f;//y

//  弾のデフォルトの速さ
	static const float shot_speed_def = 5.0f;
//  速度の減少幅
	static const float shot_speed_down = 0.5;
//  角度が大きくなったときの修正角度
	static const float repair_rad = M_PI * 350.0f / 180.0f;
//  1sをmsに直す
	static const int ms_per_s = 1000;
//  猶予時間(ms)
	static const float border_time = 1000.0f;
//  終了後待機時間
	static const int wait_end_time = 1.0 * ms_per_s;
//  弾の角度修正単位
	static const float angle_per_time = 20.0f * M_PI / 180.0f;
//  時間差到達弾の数
	static const int shot_later_roop_param = 5;
//  画面上の弾数
	static const int shot_max = 10000;

//  弾の種類
	static const enum ShotType {
		k_enemy_nomal, //通常
		k_enemy_all_renge, //全体に出す
		k_enemy_later_renge,// 時差うち
		k_enemy_lazer, //レーザー
	};
//  必須待機時間(ms)
	static const int need_wait_time = 0.2 * ms_per_s;

//  レーザーの幅
	static const int lazer_width = 20;

//  判定開始距離
	static const int start_hit_check = 60;
//  クリティカルチェック基準距離
	static const int critical_hit_check = 35;
//  得点加算音符(加算までに何分音符くらいの長さを空けるか)
	static const int score_per_hyousi = 4;

//  再開カウント数(ms)
	static const int restart_count_up = 3 * ms_per_s;
//  難易度ビットチェック用
	static const enum Defficulter {
		k_music_easy = 1 << 0, //簡単
		k_music_nomal = 1 << 1, //普通
		k_music_hard = 1 << 2, //難しい
		k_music_beyond = 1 << 3, //凄く難しい
	};
//  難易度の個数
	static const int defficulter_max = 4;

//  背景透明度
	static const float alpha_back = 0.8f;

}

#endif // !__DEFINING_DRAWING_H__



