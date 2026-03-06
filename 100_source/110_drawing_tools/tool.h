//-----------------------------
// @name   tool.h
// @brief  ツール系関数の宣言部
// @auther A.namami
// @date   2026/2/4  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#pragma once

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

// @絶対値の取得
// @in  int param 値
// @out int abs 絶対値
int Abs(int param);

// @カラーコードからrgb変換
// @in int color_code カラーコード
// @in int& red int& green int& blue それぞれ色素(返り値)
void ChangeColorToRgb(unsigned int color_code, int& red, int& green, int& blue);

// @rgbからカラーコード変換
// @out unsigned int カラーコード
// @in int red, int green, int blue それぞれ色素
unsigned int ChangeColorToCode(int red, int green, int blue);

//誤差考慮等価判定(1e-8 = 0.00000001)
bool AlmostEqual(double a, double b, double epsilon = 1e-8);
