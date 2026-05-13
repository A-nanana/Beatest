//-----------------------------
// @name   tool.h
// @brief  ツール系関数の宣言部
// @auther A.namami
// @date   2026/2/4  新規作成
// 　　　　2026/3/23 UTF-8からShift-JIS変換を追加
// 
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once
#include <string>


//-----------------------------
// @brief 簡単な計算系
// @      クランプとか
// @memo 
//-----------------------------

// @クランプ(汎用端っこ処理)
// @in  int& param 値, int low 下限, int max 上限
void CrampInt(int& param, int low, int max);
// @memo  CrampIntの float版
void CrampFloat(float& param, float low, float max);
// @memo  CrampIntの double版
void CrampDouble(double& param, double low, double max);

// @範囲判定
// @in  int param 値, int low 下限, int max 上限
// @out bool T/F 入っている/入っていない
bool InRenge(int param, int low, int max);
// @範囲判定(限度区別なし)
// @in  float param 値, float a , b 範囲値
// @out bool T/F 入っている/入っていない
bool InRenge2(float param, float a, float b);


// @絶対値の取得
// @in  int param 値
// @out int abs 絶対値
int Abs(int param);

// @カラーコードからrgb変換
// @in int color_code カラーコード(24bit)
// @in int& red int& green int& blue それぞれ色素(返り値)
void ChangeColorToRgb(unsigned int color_code, int& red, int& green, int& blue);

// @rgbからカラーコード変換
// @in int red, int green, int blue それぞれ色素
// @in int color_bit ウィンドウカラービット
// @out unsigned int カラーコード
unsigned int ChangeColorToCode(int red, int green, int blue, int color_bit);

// @誤差考慮等価判定(1e-8 = 0.00000001)
// @in double a, double b  それぞれ比較したい値, double epsilon  許容範囲
// @out bool T/F 等しい/等しくない
bool AlmostEqual(double a, double b, double epsilon = 1e-8);

// @ビットフラグが何番目か調べる
// @in int flg 調べるフラグ
// @out int 番号
int ChangeBitToNum(int flg);

//-----------------------------
// @brief コード変換系
// @      クランプとか
// @memo  調べたものが多いです。
// 　　　 そのため、メモおおめ
//-----------------------------

// @UTF-8からShift-JISに変える
// @in const char* utf8 UTF-8	の文字
// @out std::string Shift-JISの文字
std::string ToShiftJis(const char* utf8);

// @Shift-JISからUTF-8に変える
// @in const char* sift_jis Shift-JIS	の文字
// @out std::string UTF-8の文字
std::string ToUtf8(const char* sift_jis);
