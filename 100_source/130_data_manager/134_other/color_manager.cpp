//-----------------------------
// @name   color_manager.cpp
// @brief  色管理 クラス
// @auther A.namami
// @date   2026/5/14  新規作成
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------
#include "color_manager.h"
#include "../../100_source/110_drawing_tools/defining.h"

//-----------------------------
// @name   ColorSet
// @brief  色 クラス
// @memo   色の設計用
//         要素の一括保存にどうぞ
//         Dxライブラリ準拠
//------------------------------

ColorSet::ColorSet()
{
	rgb_[k_red] = 0;
	rgb_[k_green] = 0;
	rgb_[k_blue] = 0;
}

ColorSet::ColorSet(int r, int g, int b)
{
	rgb_[k_red] = 0;
	rgb_[k_green] = 0;
	rgb_[k_blue] = 0;

	SetColor3(r, g, b);
}

void ColorSet::SetColor3(int r, int g, int b)
{
	//rが-1以外なら
	if (r != -1) {
		rgb_[k_red] = r;
	}
	//gが-1以外なら
	if (g != -1) {
		rgb_[k_green] = r;
	}
	//bが-1以外なら
	if (b != -1) {
		rgb_[k_blue] = r;
	}
}


//-----------------------------
// @name   ColorManager
// @brief  色 管理クラス
// @memo   色の管理用
//         Dxライブラリ準拠
//------------------------------

ColorManager* ColorManager::instance_ = nullptr;

ColorManager::ColorManager() {
	AddColor(250, 178, 123, string_set::font_midasi1);
	AddColor(240, 240, 240, string_set::font_midasi2);
	AddColor(245, 170, 23, string_set::font_nomal1);
	AddColor(240, 0, 0, string_set::font_secure);
	AddColor(255, 0, 255, string_set::font_eff1);
	AddColor(0, 255, 255, string_set::font_eff2);
}

ColorManager::~ColorManager() {
	//ポインタ削除
	for (auto color:color_) {
		delete color.second;
	}
}
ColorManager* ColorManager::GetInstance() {
	//存在しないなら作成
	if (instance_ == nullptr) {
		instance_ = new ColorManager();
	}
	return instance_;
}

void ColorManager::AddColor(int red, int green, int blue, const char* collect_name)
{
	//既にあるなら更新する
	if (color_.count(collect_name)) {
		color_[collect_name]->SetColor3(red, green, blue);
		return;
	}
	//ないなら作成
	color_[collect_name] = new ColorSet(red, green, blue);
}

void ColorManager::AddColor(ColorSet* color, const char* collect_name)
{
	color_[collect_name] = color;
}

unsigned int ColorManager::SerchColor(const char* collect_name)
{
	//なければ黒を返す
	if (color_.count(collect_name) <= 0) {
		return GetColor(0, 0, 0);
	}
	return color_[collect_name]->ColorCode();
}
